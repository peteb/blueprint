#include "omniview.h"
#include "common.h"

#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

#include <glog/logging.h>

using namespace vw;

// -------------------------------------------------------------------------------------------------

OmniView::OmniView( )
    : m_current_scan(0)
{
}

// -------------------------------------------------------------------------------------------------

OmniView::~OmniView( )
{
}

// -------------------------------------------------------------------------------------------------

void OmniView::set_data_source( const char* data, int x, int y )
{
    m_data.resize(x*y);
    std::copy(data, data + x*y, m_data.begin());
    m_data_width = x;
    m_data_height = y;
}

// -------------------------------------------------------------------------------------------------

void OmniView::update_entity_position( int x, int y )
{
    m_entity_x = x;
    m_entity_y = y;
    scan();
}

// -------------------------------------------------------------------------------------------------

void OmniView::scan()
{
    scan_octant_1( );
    scan_octant_2( );
    scan_octant_3( );
    scan_octant_4( );
    scan_octant_5( );
    scan_octant_6( );
    scan_octant_7( );
    scan_octant_8( );
}

// -------------------------------------------------------------------------------------------------

// The 8 octant functions

//  Scans is performed row by row, going from the leftmost
//  cell to the rightmost cell in each row.
void OmniView::scan_octant_1( )
{
    float start_slope = 1.0;
    float end_slope = 0.0;
    size_t depth = 0;
    tmp_map = m_data;
    recurse_scan( start_slope, end_slope, depth  );
}

// -------------------------------------------------------------------------------------------------

void OmniView::scan_octant_2( )
{
}

// -------------------------------------------------------------------------------------------------

void OmniView::scan_octant_3( )
{
}

// -------------------------------------------------------------------------------------------------

void OmniView::scan_octant_4( )
{
}

// -------------------------------------------------------------------------------------------------

void OmniView::scan_octant_5( )
{
}

// -------------------------------------------------------------------------------------------------

//  Scans is performed row by row, going from the leftmost
//  cell to the rightmost cell in each row.
void OmniView::scan_octant_6( )
{
}

// -------------------------------------------------------------------------------------------------

void OmniView::scan_octant_7( )
{
}

// -------------------------------------------------------------------------------------------------

void OmniView::scan_octant_8( )
{
}

// -------------------------------------------------------------------------------------------------

void OmniView::print_map( const char* map, int x, int y )
{
    std::string line_out;
    for ( int k = 0; k < y; k++ ) {
        for ( int j = 0; j < x; j++ ) {
            line_out += map[ k * x + j ];
            if ( ( int ) line_out.size( ) == x ) {
                std::cerr << line_out << std::endl;
                line_out.clear( );
            }
        }
    }
}

// -------------------------------------------------------------------------------------------------

// This is applied to y when decrementing.
void OmniView::print_x( float x_start, float y_start )
{
    tmp_map[ y_start * m_data_width + x_start ] = 'X';
    print_map( tmp_map.data( ), m_data_width, m_data_height );
}

// -------------------------------------------------------------------------------------------------

void OmniView::print_scan( float y_start, float x_start, size_t depth )
{
    tmp_map[ y_start * m_data_width + x_start ] = 0x30 + depth;
    print_map( tmp_map.data(), m_data_width, m_data_height );
}

// -------------------------------------------------------------------------------------------------

void OmniView::recurse_scan( float start_slope, float end_slope, size_t depth )
{
    depth++;
    float x_start = m_entity_x;
    float y_start = m_entity_y;
    y_start -= m_current_scan;
    
    bool last_was_blocker = false;
    while ( y_start-- > 0 ) {
        // Offset is the unmodified length of the horizontal "bar" that is being scanned
        int y_bar_width = m_entity_y - (y_start - 1);
        int y_bar_width_start = y_bar_width * start_slope;
        int y_bar_width_end = y_bar_width * end_slope;
        y_bar_width = std::abs( y_bar_width_start - y_bar_width_end );
        x_start = m_entity_x - y_bar_width_start;
        // Gets number of steps before end of line as adjusted by scan_end_offset
        for ( int step = 0; step < y_bar_width ; step++, ++x_start )
        {
            if ( m_data[ y_start * m_data_width + x_start ] == WALL ) {
                print_x( x_start, y_start );
                last_was_blocker = true;
                continue;
            } else {
                // When a blocking cell is found a recusive scan is started covering
                // The area further away up until the first cell in shadow of the blocker
                if ( last_was_blocker == true ) {
                    // If this scan is coming from the left, and hit a wall, update the
                    // end_slope
                    m_current_scan += 2;
                    recurse_scan( start_slope,
                                  fabs( ( m_entity_x - x_start ) /
                                        ( m_entity_y - y_start ) ),
                                  depth );
                }
            }
            if ( last_was_blocker && x_start > m_entity_x ) {
                // If this scan is finding a space to the right, just update the start_slope
                start_slope = fabs( ( m_entity_x - x_start ) /
                                    ( m_entity_y - y_start ) );
            }
            print_scan(y_start, x_start, depth);
        
        }
    }
}
    
