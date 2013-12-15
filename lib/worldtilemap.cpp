#include "statictilemap.h"
#include "tileloader.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

#include <algorithm>

using namespace vm;

void StaticTiledMap::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
    u_int32_t left = 0;
    u_int32_t right = 0;
    u_int32_t top = 0;
    u_int32_t bottom = 0;

    // Get chunk indices into which top left and bottom right points of view fall:
    sf::Vector2f temp = target.getView( ).getCenter( ) -
        ( target.getView( ).getSize( ) / 2.f ); //get top left point of view
    left = static_cast< u_int32_t >( temp.x / ( CHUNK_SIZE * TILE_SIZE ) );
    top = static_cast< u_int32_t >( temp.y / ( CHUNK_SIZE * TILE_SIZE ) );
    temp += target.getView( ).getSize( ); //get bottom right point of view
    right = 1 + static_cast< u_int32_t >( temp.x / ( CHUNK_SIZE * TILE_SIZE ) );
    bottom = 1 + static_cast< u_int32_t >( temp.y / ( CHUNK_SIZE * TILE_SIZE ) );

    // Clamp these to fit into array bounds:
    left = std::max( ( u_int32_t )0, std::min( left, m_chunks_x ) );
    top = std::max( ( u_int32_t )0, std::min( top, m_chunks_y ) );
    right = std::max( ( u_int32_t )0, std::min( right, m_chunks_x ) );
    bottom = std::max( ( u_int32_t )0, std::min( bottom, m_chunks_y ) );

    //set texture and draw visible chunks:
    states.texture = &m_texture;
    for( u_int32_t ix = left; ix < right; ++ix )
    {
        for( u_int32_t iy = top; iy < bottom; ++iy )
        {
            target.draw( m_chunks[ ix ][ iy ], states );
        }
    }
}

StaticTiledMap::StaticTiledMap( void )
{
}

void StaticTiledMap::load_from( TileLoader* gloader )
{
    m_texture.loadFromFile( gloader->get_data( ).texture_name );
    m_map_x = gloader->get_data( ).mapx;
    m_map_y = gloader->get_data( ).mapy;
    if( ( m_map_x * m_map_y ) == 0 ) // empty map - possibly forgotten to fill data struct
    {
        m_chunks_x = 0;
        m_chunks_y = 0;
        m_chunks.clear();
        return;
    }
    m_chunks_x = ( m_map_x / CHUNK_SIZE ) + 1;
    m_chunks_y = ( m_map_y / CHUNK_SIZE ) + 1;

    // Ready up empty 2d arrays
    m_chunks.assign( m_chunks_x, std::vector< sf::VertexArray >( m_chunks_y, sf::VertexArray( sf::Quads ) ) );
    for( u_int32_t iy = 0; iy < m_map_y; ++iy )
    {
        for( u_int32_t ix = 0; ix < m_map_x; ++ix )
        {
            gloader->append_tile( ix, iy, m_chunks[ ix / CHUNK_SIZE ][ iy / CHUNK_SIZE ]);
        }
    }
}
