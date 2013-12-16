#ifndef _STATIC_TILED_MAP_
#define _STATIC_TILED_MAP_

// Own
#include "tileloader.h"

// SFML
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

// std
#include <vector>

namespace VW
{

class WorldTileMap : public sf::Drawable
{
public:
    enum {
        TILE_SIZE = 32,
        CHUNK_SIZE = 32
    };

    WorldTileMap( void );
    virtual ~WorldTileMap( void ) { }

    void load_from( TileLoader* gloader );
private:
    virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const;

    sf::Texture m_texture;
    u_int32_t m_map_x = 0;
    u_int32_t m_map_y = 0;
    u_int32_t m_chunks_x = 0;
    u_int32_t m_chunks_y = 0;

    std::vector<std::vector<sf::VertexArray> > m_chunks;
};

} // namespace VW

#endif //STATIC_TILED_MAP_
