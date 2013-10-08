#ifndef _OMNIVIEW_H_
#define _OMNIVIEW_H_

/* FOV using recursive shadowcasting.

   Shadowcasting divides the FOV calculations into eight octants and visits
   the mapcells in a totally different way than normal raycasting.
   Instead of tracing lines from the center out to the edges, shadowcasting visits
   mapcells row by row or column by column, starting with the nearest row or column
   and working it's way outward.

   When a scan comes across a cell that blocks LOS it calculates which other cells
   in rows/columns farther away that isn't visible because of the blocker.
   Those cells are "in shadow", hence the term shadowcasting.

   Definitions

   In order to understand recursive shadowcasting one need to understand what the
   slope and inverse slope of a line means. The slope is calculated using this
   simple formula:

   slope = (x1 - x2) / (y1 - y2)

   If we draw a line between [6,6] and [5,3] the slope would be:

   slope = (6 - 5) / (6 - 3) = 1 / 3 = 0.33333

   If we were to walk along this line we would find that for each step that we
   decreased y, x would be decreased 0.3333.

   Recursive Shadowcasting

   Recursive shadowcasting divides the field of view into eight octants with
   shared edges.
   The field of view will look like this when the octants are marked:

             Shared
             edge by
  Shared     1 & 2      Shared
  edge by\      |      /edge by
  1 & 8   \     |     / 2 & 3
           \1111|2222/
           8\111|222/3
           88\11|22/33
           888\1|2/333
  Shared   8888\|/3333  Shared
  edge by-------@-------edge by
  7 & 8    7777/|\4444  3 & 4
           777/6|5\444
           77/66|55\44
           7/666|555\4
           /6666|5555\
  Shared  /     |     \ Shared
  edge by/      |      \edge by
  6 & 7      Shared     4 & 5
             edge by
             5 & 6

  As with normal shadowcasting, this recursive shadowcasting algorithm scans
  an octant row by row or column by column, depending on the octant.
  In each octant the rows/columns closest to the starting point are scanned first.

  In octant 1 and 6 the scans are performed row by row, going from the leftmost
  cell to the rightmost cell in each row.

  In octant 2 and 5 the scans are performed row by row, going from the rightmost
  cell to the leftmost cell in each row.

  In octant 3 and 8 the scans are performed column by column, going from the
  topmost cell to the bottom most cell in each column.

  In octant 4 and 7 the scans are performed column by column, going from the
  bottom most cell to the topmost cell in each column.

  When a blocking cell is found a new scan is recursivly started one row/column
  further away, covering the area up until the first cell in shadow of the blocker.
  The rest of the initial row/column is scanned and subsequent blocking cells
  directly adjacent to the initial blocker is skipped.
  If a new section of non-blocking cells, followed by a blocker, is found the
  procedure is repeated.

  The area that we wish to calculate a field of view for looks like this:

  ................. 16  @ = starting cell
   ......###....... 15  # = blocking cell
    .....###....... 14  . = non-blocking cell
     ....###..#..## 13
      ...##........ 12
       ............ 11
        ........... 10
         .......... 9
          ......... 8
           ........ 7
            ....... 6
             ...... 5
              ..... 4
               .... 3
                ... 2
                 .. 1
                  @

  Rows 1 through 11 are all scanned without any problems from left to right.
  When the rightmost cell is reached a new scan is started one row further away,
  just as described before.

  If we were to draw a line from the center of the starting cell to the center
  of the leftmost cell in any of these rows we would find that the slope is 1.
  We call this the scan's start slope.
  If we would do the same for the rightmost cell the slope would be 0.
  This slope is ofcourse called the end slope.

  When we reach the 12th row things are becoming a bit more interesting.
  The recursion is started when we get to row 12 and hit the blocking cells.

  ................. 16  # = blocking cell
   ......###....... 15  . = non-blocking cell
    .....###....... 14
     ....###..#..## 13
      ...x#........ 12  x = first blocking cell

  When the first blocking cell is hit (x) a new scan is started on row 13.
  The start slope is ofcourse the same as for all of the previous rows (ie. 1),
  but the end slope is different.
  The end slope is calculated using a line from the starting point to a point
  that 'brushes' by to the left of the blocking cell.
  If we zoom in it looks something like this:

  +---+xxxxx#####  x = first blocking cell
  |   |xxxxx#####  a = point that 'brushes' by to
  |   |xxxxx#####      the left of the blocking cell
  |   |xxxxx#####
  +---axxxxx#####
  +---++---++---+
  |   ||   ||   |
  |   ||   ||   |
  |   ||   ||   |
  +---++---++---+

  Thus, the end slope is obtained using a line from the center starting cell
  to the point marked 'a' in the figure. This gives an end slope of about 0.82.

  Ok, so now we have two scans; the original that continues to scan row 12 until
  the rightmost cell is reached and a new scan that scans row 13 from the
  leftmost cell (start slope 1) to the cell at row 13 that intersects the line
  with a slope of 0.82 (end slope):

  2222............. 16  # = blocking cell
   2222..###....... 15  . = non-blocking cell
    222..###....... 14
     222.###..#..## 13  1 = original scan
      111##11111111 12  2 = new scan

  Lets return to the original scan on row 12.
  The scan had just come across the first blocking cell and recursivly started a
  new scan one row further away with a new end slope.
  The original scan now checks the next cell and finds that this one is also a
  blocking cell.
  Since the previous cell was a blocking cell too, we have come across a section
  of blocker and just continue scanning until we reach a non blocking cell:

  ................. 16  # = blocking cell
   ......###....... 15  . = non-blocking cell
    .....###....... 14
     ....###..#..## 13
      ...##o....... 12  o = first non-blocking cell after a section of blockers

  When the first non-blocking cell is found after a section of blockers we need
  to calculate a new start slope for the scan.
  This is done using a line from the center of the starting cell to a point that
  'brushes' by to the right of the blocking cell.
  If we zoom in it looks something like this:

  ##########aoooo  o = first non-blocking cell
  ##########o   o  a = point that 'brushes' by to the
  ##########o   o      right of the blocking cell
  ##########o   o
  ##########ooooo
  +---++---++---+
  |   ||   ||   |
  |   ||   ||   |
  |   ||   ||   |
  +---++---++---+

  Thus, the new start slope of the original scan is obtained using a
  line from the center of the starting cell to the point marked 'a'
  in the figure.
  This gives a start slope of 0.6.

  Ok, once a scan has reached it's last cell the scan is finished and a new scan
  is started one row further away if, and only if, the last cell was a
  non-blocking cell.
  In the case of our original scan the last cell was a non-blocking cell so a new
  scan is started one row further away with the new start slope of
  0.6 (instead of the old 1).

  When the original scan starts on row 13 a blocking cell is immediately found:

  ................. 16  # = blocking cell
   ......###....... 15  . = non-blocking cell
    .....###....... 14
     ....##x..#..## 13  x = blocking cell in original scan

  When this happens we continue scanning until a non-blocking cell is found.
  In this case the next cell is a non-blocking cell and we calculate a new start
  slope in the same manner as on row 12 when we passed the section of blockers.
  After this is done we continue to scan from left to right until we reach the
  last cell or until we hit a blocking cell.
  In our example a blocking cell is found before we reach the last cell:

  ................. 16  # = blocking cell
   ......###....... 15  . = non-blocking cell
    .....###....... 14
     ....##...x..## 13  x = blocking cell in original scan

  A new scan is now recursively started in the same way as on row 12.
  The scan has the same start slope as the original scan (0.6) and an end slope
  of a line that 'brushes' by to the left of the blocking cell.
  Now we have three active scans:

  2222......33..... 16
   2222..##333..... 15
    222..##333..... 14
     222.###11#11## 13

  The same procedure is repeated once more when we move out of the blocking cell,
  find two new non-blocking cells and the run into yet another blocking cell:

  2222......33444.. 16
   2222..##333.44.. 15
    222..##333.44.. 14
     222.##111#11## 13

  When the original scan ends at the rightmost cell in row 13 we end with a blocking
  instead of a non-blocking, as we did in row 12.
  Since the original scan ended with a blocking cell a new scan is NOT started one
  row further away.
  We now have scan 2, 3 and 4 to do the job of scanning the rest of the field of view.
  These scans follow the same procedures and rules as the original scan.

When the scans are done we get this field of view:

 ....ssssss.....ss 16  @ = starting cell
  ....ssss#..s..ss 15  # = blocking cell
   ...ssss#..s..ss 14  . = non-blocking cell
    ...ss##..#..## 13  s = shadowed cells
     ...##........ 12
      ............ 11
       ........... 10
        .......... 9
         ......... 8
          ........ 7
           ....... 6
            ...... 5
             ..... 4
              .... 3
               ... 2
                .. 1
                 @

This procedure is repeated on the other octants, thus producing a complete field of view.

*/

#include <cstdlib>
#include <string>
#include <vector>

namespace vw
{

class OmniView
{
public:
    OmniView();
    ~OmniView();

    /**
     * Sets the data source (screen image to use)
     * To calculate shadowcasting for.
     *
     * @param data Pointer to data
     * @param x x size of area
     * @param y y size of area
     *
     * @return
     */
    void set_data_source( const char* data, int x, int y );

    void update_entity_position( int x, int y );

    void scan( );
    void scan_octant_1( );
    void scan_octant_2( );
    void scan_octant_3( );
    void scan_octant_4( );
    void scan_octant_5( );
    void scan_octant_6( );
    void scan_octant_7( );
    void scan_octant_8( );

    void print_map( const char* map, int x, int y );

    enum OCTANTS {
        OCTANT_1,
        OCTANT_2,
        OCTANT_3,
        OCTANT_4,
        OCTANT_5,
        OCTANT_6,
        OCTANT_7,
        OCTANT_8
    };

    void recurse_scan( int x, int y, OCTANTS octant, float start_slope = 1.0f,
                       float end_slope = 0.0f, bool shadow = false );
private:
    std::vector<char> tmp_map;
    std::vector<char> m_data;
    int m_entity_x;
    int m_entity_y;
    int m_data_width;
    int m_data_height;
};

} // Void namespace
#endif /* _OMNIVIEW_H_ */
