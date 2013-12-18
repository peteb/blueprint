#ifndef _TILEMAP_H_
#define _TILEMAP_H_

// std
#include <string>

// SFML
#include <SFML/Graphics.hpp>

class TileMap: public sf::Drawable, public sf::Transformable
{
public:
    TileMap();

     bool load( const std::string& tileset, sf::Vector2u tile_size, const u_int32_t* tiles,
               u_int32_t width, u_int32_t height );

    virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const
    {
        // apply the transform
        states.transform *= getTransform( );
        // apply the tileset texture
        states.texture = &m_tileset;
        // draw the vertex array
        target.draw( m_vertices, states );
    }

private:
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;

};

#endif // _TILEMAP_H
