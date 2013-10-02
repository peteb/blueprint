#ifndef ASTAR_H
#define ASTAR_H

// Own

#include "astar.h"

// Std includes
#include <new>
#include <vector>
#include <algorithm>
using namespace star;

// Public Methods -----------------------------------------

// Scan the 8 positions around the center
static int square_check[] = {
   -1, -1, 0, -1, 1, -1,
   -1,  0,        1,  0,
   -1,  1, 0,  1, 1,  1
};

const static int LINEAR_COST = 10;
const static int DIAGONAL_COST = 14;

AStar::AStar( )
   : m_enable_debug(false)
   , m_current_bound(0)
   , m_map_size_x(0)
   , m_map_size_y(0)
   , m_start_position(0)
{
}

AStar::AStar( WeightValues array, int x, int y )
   : m_enable_debug(false)
   , m_current_bound(0)
   , m_map_size_x(0)
   , m_map_size_y(0)
   , m_start_position(0)
{
   m_map_size_x = x;
   m_map_size_y = y;
   m_current_bound = array;
}

AStar::~AStar( )
{
   cleanup();
}

void AStar::cleanup( )
{
   // Cleaning up the open list
   PositionList::iterator it_p = m_open_position_list.begin(),
      it_e = m_open_position_list.end();
   while (it_p != it_e) {
      delete it_p->second;
      ++it_p;
   }
   // Cleaning up the closed list
   it_p = m_closed_position_list.begin(), it_e = m_closed_position_list.end();
   while (it_p != it_e) {
      delete it_p->second;
      ++it_p;
   }
}

bool AStar::bind(WeightValues array, int x, int y, bool copy )
{
   if (array && x && y) {
      m_map_size_x = x;
      m_map_size_y = y;
      m_current_bound = array;
      return true;
   }
   return false;
}

void AStar::size(int x, int y)
{
}

LayerID AStar::add_penalty_layer( const WeightValues array, size_t size )
{
   return 0;
}

bool AStar::remove_penalty_layer( LayerID id )
{
   return true;
}

bool AStar::astar( int from_x, int from_y, int to_x, int to_y,
                   bool ignore_blocked, const int** path )
{
   if (!m_current_bound ) {
      return false;
   }
   // Verify that we the start position is possible
   if (!ignore_blocked) {
      if (m_current_bound[from_y * from_x + from_x] == 0) {
         return false;
      }
   }
   // Go through the map and remove untraversable terrain to the
   // closed list, untraversable terrain equals terrain with a value
   // of 0
   int position = 0;
   for (int i = 0; i < m_map_size_y; i++) {
      for (int j = 0; j < m_map_size_x; j++) {
         position = i * m_map_size_x + j;
         if (m_current_bound[position] == 0) {
            DEBUG("Moved " << j << "," << i << " to closed list" << std::endl);
            Entry* entry = 0;
            entry = new (std::nothrow) Entry();
            if (!entry) {
               return false;
            }
            entry->blocked = true;
            entry->position = position;
            entry->costs.g_score = 0; // Will never move to this so zero it
            entry->costs.h_score = 0; // The heuristic doesn't matter
            entry->parent = 0;        // Start has no parent

            add_closed_list_entry_by_position(position, entry);
         }
      }
   }

   // Save the start position away
   m_start_position = from_y * m_map_size_x + from_x;
   m_end_position = m_map_size_x * to_y + to_x;

   // Now take the start point and add it to the open list
   Entry* entry = 0;
   entry = new (std::nothrow) Entry();
   entry->blocked = false;
   entry->position = m_start_position;
   entry->costs.g_score = 0;
   entry->costs.h_score = 0;
   entry->parent = 0;
   add_open_list_entry_by_position(m_start_position, entry);

   // Now build the open list.
   m_active_position = m_start_position;
   if (!build_open_list()) {
      reset_data();
      return false;
   }
   *path = m_path_copy;
   return true;
}

void AStar::add_open_list_entry_by_position(Position pos, Entry* entry)
{
   m_open_score_list.insert(std::make_pair(entry->costs.h_score + entry->costs.g_score, entry));
   m_open_position_list[pos] = entry;
}

// No need to check the closed list for duplicate entries as they already been
// removed in the open list.
void AStar::add_closed_list_entry_by_position(Position pos, Entry *entry)
{
   m_closed_score_list.insert(std::make_pair(entry->costs.h_score + entry->costs.g_score, entry));
   m_closed_position_list[pos] = entry;
}

bool AStar::change_open_to_closed(Entry *entry)
{
   int score = entry->costs.g_score + entry->costs.h_score;
   size_t count = m_open_score_list.count(score);
   std::pair<ScoreList::iterator, ScoreList::iterator> ret;
   ret = m_open_score_list.equal_range(score);
   ScoreList::iterator it_f = ret.first, it_e = ret.second;
   while (it_f != it_e) {
      if (it_f->second->position == entry->position) {
         break;
      }
      ++it_f;
   }
   // Now the correct entry has been found; it_f is pointing to it.
   m_closed_score_list.insert(std::make_pair(score, entry));
   // Erasing this score entry as the other score entry with the same score will be used
   m_open_score_list.erase(it_f);
   m_closed_position_list.insert(std::make_pair(entry->position, entry));
   m_open_position_list.erase(entry->position);
   return true;
}

void AStar::enable_debug_dump(bool enable)
{
   m_enable_debug = enable;
}

bool AStar::build_open_list()
{
   Entry* active_entry = 0;
   Position pos = 0;
   Position pos_x = 0;
   Position pos_y = 0;
   Position end_x = m_end_position % m_map_size_x;
   Position end_y = m_end_position / m_map_size_x;
   int size = sizeof(square_check) / sizeof(square_check[0]);
   int tentative_g_score = 0;
   // Only checking position list as both score and position should be synced
   while (m_open_position_list.size() > 0 && m_open_score_list.size() > 0)
      {
         // Get the lowest m_open_list (which is the topmost)
         active_entry = m_open_score_list.begin()->second;
         if (active_entry->position == m_end_position) {
            break;
         }
         change_open_to_closed(m_open_score_list.begin()->second);
         for (int j = 0; j < size; j += 2) {
            pos_x = active_entry->position % m_map_size_x;
            pos_y = active_entry->position / m_map_size_x;

            // Check for blocked squares
            if (pos_x + square_check[j] < 0 ||
                pos_x + square_check[j] > m_map_size_x - 1) {
               continue; // Skipping out of bounds on x
            } else {
               pos_x += square_check[j];
            }
            if (pos_y + square_check[j + 1] < 0 ||
                pos_y + square_check[j + 1] > m_map_size_y - 1) {
               continue; // Skipping out of bounds on y
            } else {
               pos_y += square_check[j + 1];
            }

            // If not blocked get this position
            pos = pos_y * m_map_size_x + pos_x;

            // Check if this position is in the closed list, if so take next position
            if (m_closed_position_list.find(pos) != m_closed_position_list.end()) {
               continue;
            }

            if (j == 0 || j == 4 || j == 10 || j == 14) {
               tentative_g_score = active_entry->costs.g_score + DIAGONAL_COST;
            } else {
               tentative_g_score = active_entry->costs.g_score + LINEAR_COST;
            }

            // Check if the new position already is in the open list
            bool new_entry = false;
            Entry* child_position = 0;
            PositionList::iterator it = m_open_position_list.find(pos);
            if (it != m_open_position_list.end()) {
               child_position = it->second; // Found an old entry
               // Check if the path from this square to that one is better

               if (tentative_g_score >= child_position->costs.g_score) {
                  // If this square not is better than the open square don't do anything
                  continue;
               }
               child_position->parent = active_entry;
               child_position->costs.g_score = tentative_g_score;
               continue;
            } else {
               // As entry did not exist in list, create it
               child_position = new (std::nothrow) Entry();
               new_entry = true;
               child_position->blocked = false;
               child_position->position = pos;
               child_position->parent = active_entry;
               child_position->costs.g_score = tentative_g_score;
            }
            child_position->costs.h_score = (std::abs(pos_x - end_x)) + (std::abs(pos_y - end_y)) * 10;
            DEBUG("Adding X:" << pos_x << " Y:" << pos_y << " to open list" << std::endl);
            DEBUG("g:" << child_position->costs.g_score << " h:" << child_position->costs.h_score
                  << " Total:" << child_position->costs.g_score + child_position->costs.h_score << std::endl);
            if (new_entry) {
               add_open_list_entry_by_position(pos, child_position);
            }
         }
         if (m_open_position_list.empty()) {
            DEBUG("No path found!" << std::endl);
            reset_data();
            return false;
         }
         m_best_scored_position = m_open_score_list.begin()->second->position;
         DEBUG("Best scored position is: X:" << m_open_score_list.begin()->second->position % m_map_size_x
               << " Y:" << m_open_score_list.begin()->second->position / m_map_size_x
               << " with a score of " << m_open_score_list.begin()->first << std::endl);
      }
   return buildPath(active_entry);
}

void AStar::reset_data()
{
   m_open_position_list.clear();
   m_open_score_list.clear();
   m_closed_position_list.clear();
   m_closed_score_list.clear();
   m_path_result.clear();
}

bool AStar::buildPath(const Entry* parentEntry)
{
   const Entry* e = parentEntry;
   while (e) {
      m_path_result.push_front(e->position);
      e = e->parent;
   }
   // Once the path is done, make a copy of it so the ownership
   // can be handed over.
   int size = m_path_result.size();
   m_path_copy = new (std::nothrow) int[size + 1];
   if (!m_path_copy) {
      return false;
   }
   m_path_copy[0] = size;
   for (int i = 1; i < size; i++) {
      m_path_copy[i] = m_path_result[i - 1];
   }
   if (m_enable_debug) {
      debugDump();
   }
   reset_data();
   return true;
}

void AStar::debugDump()
{
   std::vector<char> map_ascii;
   map_ascii.resize(m_map_size_x * m_map_size_y);

   // Start
   for (int i = 0; i < m_map_size_x * m_map_size_y; i++) {
      switch (m_current_bound[i])
         {
         case 0:
            map_ascii[i] = '#';
            continue;
         default:
            map_ascii[i] = '-';
            continue;
         }
   }

   //   // Overlay resolved open and closed entries
   //    PositionList::const_iterator it_a = m_open_position_list.begin(), it_b = m_open_position_list.end();
   //    while (it_a != it_b) {
   //        map_ascii[it_a->first] = 'o';
   //        ++it_a;
   //    }
   //    it_a = m_closed_position_list.begin(), it_b = m_closed_position_list.end();
   //    while (it_a != it_b) {
   //        map_ascii[it_a->first] = 'c';
   //        ++it_a;
   //    }

   // Draw the resulting path
   for (int i = 0; i < m_path_result.size(); i++) {
      map_ascii[m_path_result[i]] = 'x';
   }
   // Highlight best position
   map_ascii[m_best_scored_position] = 'B';
   // Add start and end indicators
   map_ascii[m_start_position] = 'S';
   map_ascii[m_end_position] = 'E';
   std::string line_out;
   // Output map
   std::cout << std::flush;
   for (int k = 0; k < m_map_size_y; k++) {
      for (int j = 0; j < m_map_size_x; j++) {
         line_out += map_ascii[k * m_map_size_x + j];
         if (line_out.size() == m_map_size_x) {
            std::cout << line_out << std::endl;
            line_out.clear();
         }
      }
   }
}

#endif // ASTAR_H
