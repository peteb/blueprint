#ifndef _STATIC_TILED_MAP_
#define _STATIC_TILED_MAP_

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <vector>

class TileLoader;
class StaticTiledMap : public sf::Drawable
{
private:
    enum { 
        TILE_SIZE = 64,
        CHUNK_SIZE = 32
    };
    virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const;
    sf::Texture m_texture;
    u_int32_t map_x;
    u_int32_t map_y;
    u_int32_t chunks_x;
    u_int32_t chunks_y;

    std::vector<std::vector<sf::VertexArray> > m_chunks;
public:
    StaticTiledMap( void );
    virtual ~StaticTiledMap( void ) { };
    void load_from( TileLoader* gloader);
};

#endif //STATIC_TILED_MAP_INCLUDED
