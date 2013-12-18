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
    left = static_cast< uint32 >( temp.x / ( md.chunk_size * md.tile_size ) );
    top = static_cast< uint32 >( temp.y / ( md.chunk_size * md.tile_size ) );
    temp += target.getView( ).getSize( ); //get bottom right point of view
    right = 1 + static_cast< uint32 >( temp.x / ( md.chunk_size * md.tile_size ) );
    bottom = 1 + static_cast< uint32 >( temp.y / ( md.chunk_size * md.tile_size ) );

    // Clamp these to fit into array bounds:
    left = std::max( ( uint32 )0, std::min( left, md.chunks_x ) );
    top = std::max( ( uint32 )0, std::min( top, md.chunks_y ) );
    right = std::max( ( uint32 )0, std::min( right, md.chunks_x ) );
    bottom = std::max( ( uint32 )0, std::min( bottom, md.chunks_y ) );

    //set texture and draw visible chunks:
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

    md.chunks_x = ( md.mapx / md.chunk_size ) + 1;
    md.chunks_y = ( md.mapy / md.chunk_size ) + 1;

    m_chunks.assign( md.chunks_x, std::vector< sf::VertexArray >( md.chunks_y, sf::VertexArray( sf::Quads ) ) );
    for( uint32 iy = 0; iy < md.mapy; ++iy )
    {
        for( uint32 ix = 0; ix < md.mapx; ++ix )
        {
            m_world.append_tile( ix, iy, m_chunks[ ix / md.chunk_size ][ iy / md.chunk_size ]);
        }
    }
}
