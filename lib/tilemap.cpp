#include "tilemap.h"

TileMap::TileMap( )
{
}

bool TileMap::load( const std::string& tileset, sf::Vector2u tile_size,
                   const u_int32_t* tiles, u_int32_t width, u_int32_t height )
{
    if ( ! m_tileset.loadFromFile( tileset ) ) {
        return false;
    }
    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType( sf::Quads ); //a quad is simply two trianges put together
    // 4 vertices ( quad ) * height * width
    m_vertices.resize(width * height * 4);

    // populate the vertex array, with one quad per tile
    // loop through the width and height of the level
    u_int32_t tu, tv;
    for ( u_int32_t i = 0; i < width; ++i ) {
        for ( u_int32_t j = 0; j < height; ++j ) {
            // get the tile which is to be textured
            u_int32_t tile_number = tiles[ i + j * width ];
            tu = tile_number % ( m_tileset.getSize( ).x / tile_size.x );
            tv = tile_number / ( m_tileset.getSize( ).x / tile_size.x );

            sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * tile_size.x, j * tile_size.y);
            quad[1].position = sf::Vector2f((i + 1) * tile_size.x, j * tile_size.y);
            quad[2].position = sf::Vector2f((i + 1) * tile_size.x, (j + 1) * tile_size.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tile_size.y);
            
            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * tile_size.x, tv * tile_size.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tile_size.x, tv * tile_size.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tile_size.x, (tv + 1) * tile_size.y);
            quad[3].texCoords = sf::Vector2f(tu * tile_size.x, (tv + 1) * tile_size.y);
        }
    }
    return true;
}
