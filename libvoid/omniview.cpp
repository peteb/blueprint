#include "omniview.h"
#include "common.h"

using namespace world;

OmniView::OmniView( )
{
}

OmniView::~OmniView( )
{
}

void OmniView::set_data_source( const char* data, int x, int y )
{
    m_data = data;
    m_data_width = x;
    m_data_height = y;
}

void OmniView::update_entity_position( int x, int y )
{
    m_entity_x = x;
    m_entity_y = y;
    scan();
}

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

// The 8 octant functions

//  Scans is performed row by row, going from the leftmost
//  cell to the rightmost cell in each row.
void OmniView::scan_octant_1( )
{
    float slope = 1.0;
    recurse_scan( m_entity_x, m_entity_y, OCTANT_1, slope );
}

void OmniView::scan_octant_2( )
{
}

void OmniView::scan_octant_3( )
{
}

void OmniView::scan_octant_4( )
{
}

void OmniView::scan_octant_5( )
{
}

//  Scans is performed row by row, going from the leftmost
//  cell to the rightmost cell in each row.
void OmniView::scan_octant_6( )
{
}

void OmniView::scan_octant_7( )
{
}

void OmniView::scan_octant_8( )
{
}

// This is applied to y when decrementing.
void OmniView::recurse_scan( int x, int y, OmniView::OCTANTS octant, float end_slope )
{
    int x_start = x;
    int y_start = y;
    int x_step = 1;
    switch ( octant )
    {
        case OmniView::OCTANT_1:
        {
            // Get characters position
            // Find scan area
            // Verify boundaries - going up to the right
            // Scan a line
            while ( y_start > 0 ) {
                --y_start;
                while ( x_start > 0 ) {
                    --x_start;
                    if ( m_data[ x_start * y_start + x_start ] != WALL ) {
                        ++x_start;
                    } else {
                        end_slope = float(x - x_start) / float(y - y_start);
                    recurse_scan( x_start, y_start, octant );
                    }
                }
                x_start
            }
            break;
        }
    }
}
