#include "StaticTiledMap.h"
#include "TileLoader.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

void StaticTiledMap::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
    u_int32_t left = 0;
    u_int32_t right = 0;
    u_int32_t top = 0;
    u_int32_t bottom = 0;

    //get chunk indices into which top left and bottom right points of view fall:
    sf::Vector2f temp = target.getView( ).getCenter( ) -
        ( target.getView( ).getSize( ) / 2.f ); //get top left point of view
    left = static_cast< int >( temp.x / ( CHUNK_SIZE * TILE_SIZE ) );
    top = static_cast< int >( temp.y / ( CHUNK_SIZE * TILE_SIZE ) );
    temp += target.getView( ).getSize( ); //get bottom right point of view
    right = 1 + static_cast< int >( temp.x / ( chunksize * tilesize ) );
    bottom = 1 + static_cast< int >( temp.y / ( chunksize * tilesize ) );

    //clamp these to fit into array bounds:
    left = std::max( 0, std::min( left, chunks_x ) );
    top = std::max( 0, std::min( top, chunks_y ) );
    right = std::max( 0, std::min( right, chunks_x ) );
    bottom = std::max( 0, std::min( bottom, chunks_y ) );

    //set texture and draw visible chunks:
    states.texture = &m_texture;
    for( u_int32_t ix = left; ix < right; ++ix )
    {
        for(u_int32_t iy = top; iy < bottom; ++iy )
        {
            target.draw( m_chunks[ ix ][ iy ], states );
        }
    }
}
StaticTiledMap::StaticTiledMap( void )
    : map_x( 0 ),
      map_y( 0 ),
      chunks_x( 0 ),
      chunks_y( 0 )
{
}

void StaticTiledMap::load_from( TileLoader* gloader )
{
    m_texture.loadFromFile( gloader->GetData( ).TextureName );
    map_x = gloader->GetData( ).MapX;
    map_y = gloader->GetData( ).MapY;
    if( ( map_x * map_y ) ==0 ) //empty map - possibly forgotten to fill data struct
    {
        //to stop displaying at all after failed loading:
        chunks_x = 0;
        chunks_y = 0;
        m_chunks.clear();
        return;
    }
    chunks_x = ( map_x / CHUNK_SIZE ) + 1;
    chunks_y = ( map_y / CHUNK_SIZE ) + 1;
    // Ready up empty 2d arrays
    m_chunks.assign( chunks_x, std::vector< sf::VertexArray >( chunks_y, sf::VertexArray( sf::Quads ) ) );
    for(int iy = 0; iy < map_y; ++iy )
    {
        for( int ix = 0; ix < map_x; ++ix )
        {
            gloader->AppendTile( ix, iy, m_chunks[ ix / CHUNK_SIZE ][ iy / CHUNK_SIZE ]);
        }
    }
}
