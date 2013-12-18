#ifndef WORLD_MAP_H
#define WORLD_MAP_H

// own
#include "worldloader.h"
#include "common.h"

// SFML
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

// std
#include <vector>

namespace VW
{

class WorldMap : public sf::Drawable
{
public:
    WorldMap( );
    virtual ~WorldMap( void ) { }
    void setup_map(int32 map_x, int32 map_y, uint32 tile_size, uint32 chunk_size,
                   std::string &filename);
private:
    virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const;
    void init_chunks( );

    WorldLoader m_world;
    std::vector< std::vector< sf::VertexArray > > m_chunks;
};

} // namespace VW

#endif // WORLD_MAP_H
