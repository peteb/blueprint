// Own
#include "worldmap.h"
#include "tileloader.h"

// SFML
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

// std
#include <algorithm>

using namespace VW;

WorldMap::WorldMap( )
{
}

void WorldMap::setup_map( int32 map_x, int32 map_y, uint32 tile_size, uint32 chunk_size,
                          std::string& filename )
{
    // Set the texture to use for the tilemap
    m_world.get_data().m_textures.load( Textures::Landscape, filename );
    // Then set the dimensions
    m_world.setup_map( map_x, map_y, tile_size, chunk_size );
    init_chunks();
}

void WorldMap::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
    uint32 left = 0;
    uint32 right = 0;
    uint32 top = 0;
    uint32 bottom = 0;

    const MapData& md = m_world.get_data();
    // Get chunk indices into which top left and bottom right points of view fall:


    sf::Vector2f temp = target.getView( ).getCenter( ) -
        ( target.getView( ).getSize( ) / 2.f ); //get top left point of view
    left = static_cast< uint32 >( temp.x / ( md.m_chunk_size * md.m_tile_size ) );
    top = static_cast< uint32 >( temp.y / ( md.m_chunk_size * md.m_tile_size ) );
    temp += target.getView( ).getSize( ); //get bottom right point of view
    right = 1 + static_cast< uint32 >( temp.x / ( md.m_chunk_size * md.m_tile_size ) );
    bottom = 1 + static_cast< uint32 >( temp.y / ( md.m_chunk_size * md.m_tile_size ) );

    // Clamp these to fit into array bounds:
    left = std::max( ( uint32 )0, std::min( left, md.m_chunks_x ) );
    top = std::max( ( uint32 )0, std::min( top, md.m_chunks_y ) );
    right = std::max( ( uint32 )0, std::min( right, md.m_chunks_x ) );
    bottom = std::max( ( uint32 )0, std::min( bottom, md.m_chunks_y ) );

    // Set texture and draw visible chunks:
    states.texture = &m_world.get_tilemap_texture();
    for( uint32 ix = left; ix < right; ++ix )
    {
        for( uint32 iy = top; iy < bottom; ++iy )
        {
            target.draw( m_chunks[ ix ][ iy ], states );
        }
    }
}

void WorldMap::init_chunks( )
{
    MapData& md = m_world.get_data();

    md.m_chunks_x = ( md.m_mapx / md.m_chunk_size ) + 1;
    md.m_chunks_y = ( md.m_mapy / md.m_chunk_size ) + 1;
    // Check for pregenerated chunks here
    // If not found, generate a new chunk
    m_world.create_world_chunk( md.m_chunks_x, md.m_chunks_y, md.m_chunk_size );
    m_chunks.assign( md.m_chunks_x, std::vector< sf::VertexArray >( md.m_chunks_y, sf::VertexArray( sf::Quads ) ) );
    for( uint32 iy = 0; iy < md.m_mapy; ++iy )
    {
        for( uint32 ix = 0; ix < md.m_mapx; ++ix )
        {
            m_world.append_tile( ix, iy, m_chunks[ ix / md.m_chunk_size ][ iy / md.m_chunk_size ]);
        }
    }
}
