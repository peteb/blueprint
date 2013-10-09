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
    float slope = 1.0;
    tmp_map = m_data;
    recurse_scan( m_entity_x, m_entity_y, OCTANT_1, slope );
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
static size_t recurse_count;

void OmniView::print_scan( bool shadow, float y_start, float x_start, size_t recurse_counter )
{
    if ( shadow ) {
        tmp_map[ y_start * m_data_width + x_start ] = 's';
    } else {
        tmp_map[ y_start * m_data_width + x_start ] = 0x30 + recurse_counter;
    }
    print_map( tmp_map.data(), m_data_width, m_data_height );
}

// -------------------------------------------------------------------------------------------------

void OmniView::recurse_scan( int x, int y, OmniView::OCTANTS octant, float start_slope,
                             float end_slope, bool shadow, size_t recurse_count )
{
    float x_start = x;
    float y_start = y;
    size_t r = recurse_count++;
    bool last_was_blocker = false;
    switch ( octant )
    {
        case OmniView::OCTANT_1:
        {
            --y_start;
            while ( y_start > 0 ) {
                // Offset is the unmodified length of the horizontal "bar" that is being scanned
                x_start = x;
                int y_bar_width = y - y_start + 1;
                float scan_end_offset = y_bar_width - ( y_bar_width * end_slope );
                float scan_start_offset = y_bar_width * ( 1.0f - start_slope );
                x_start -= scan_end_offset - 1;
                // Gets number of steps before end of line as adjusted by scan_end_offset
                float step_inc = 1.0f / scan_end_offset;
                for ( float step = 0.0f; step < 1.0f; step += step_inc, ++x_start )
                {
                    print_scan(shadow, y_start, x_start, recurse_count);
                    if ( m_data[ y_start * m_data_width + x_start ] == WALL ) {
                        if ( y_start == 0 ) {
                            goto out; // Too deep down to do this nicely
                        }
                        if ( ! last_was_blocker || y_start > 0 ) {
                            last_was_blocker = true;
                            print_x( x_start, y_start );
                            // Now recurse
                            recurse_scan( x_start,
                                          y_start,
                                          OCTANT_1,
                                          start_slope,
                                          fabs( ( x - x_start ) / ( y - y_start ) - 0.2f ),
                                                shadow,
                                                recurse_count );
                        } else
                        {
                            last_was_blocker = false;
                        }
                    }
                }
                --y_start;
            }
        out:
            break;
        }
    }
}
