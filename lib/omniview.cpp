#include "omniview.h"
#include "common.h"

#include <iostream>
#include <string>
#include <algorithm>

#include <glog/logging.h>

using namespace world;

OmniView::OmniView( )
{
}

OmniView::~OmniView( )
{
}

void OmniView::set_data_source( const char* data, int x, int y )
{
    m_data.resize(x*y);
    std::copy(data, data + x*y, m_data.begin());
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

void OmniView::print_map( )
{
    std::vector<char> map_data;
    map_data.resize(m_data.size());
    map_data = m_data;
    std::string line_out;
    for (int k = 0; k < m_data_height; k++) {
        for (int j = 0; j < m_data_width; j++) {
            line_out += m_data[k * m_data_width + j];
            if ((int)line_out.size() == m_data_width) {
                LOG(INFO) << line_out;
                line_out.clear();
            }
        }
    }
}
// This is applied to y when decrementing.
void OmniView::recurse_scan( int x, int y, OmniView::OCTANTS octant, float end_slope )
{
    print_map();
    return;
    int x_start = x;
    int y_start = y;
    int x_offset = x;
    int y_offset = y;
    int x_step = 1;
    switch ( octant )
    {
        case OmniView::OCTANT_1:
        {
            // Get characters position
            // Find scan area
            // Verify boundaries - going up to the right
            // Scan a line
            int sight_range = 20;
            while ( y_start > 0 && y - y_start < sight_range ) {
                --y_start;
                --x_start;
                while ( x_start > 0 && x_start >= x ) {
                    if ( m_data[ x_start * y_start + x_start ] != WALL ) {
                        print_map();
                        std::cout << "Found wall" << std::endl;
                        }
                }
                end_slope = float(x - x_start) / float(y - y_start);
                recurse_scan( x_start, y_start, octant, end_slope );
            }
            break;
        }
        
    }
}
