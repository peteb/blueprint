#ifndef TILE_LOADER
#define TILE_LOADER

// own
#include "textureholder.h"
#include "common.h"

// SFML
#include <SFML/Graphics/VertexArray.hpp>

// std
#include <string>

namespace VW
{

struct MapData
{
    TextureHolder m_textures;
    uint32 mapx = 0;
    uint32 mapy = 0;
    uint32 tile_size = 0;
    uint32 chunk_size = 0;
    uint32 chunks_x = 0;
    uint32 chunks_y = 0;
};

class TileLoader
{
public:
    TileLoader( ) { }
    virtual ~TileLoader( void ) { }
    virtual void append_tile( uint32 gx, uint32 gy, sf::VertexArray& vertex_array ) = 0;
    MapData& get_data( void ) { return m_mapdata; }
    const MapData& get_data( void ) const { return m_mapdata; }
protected:
    MapData m_mapdata;

};

} // namespace VW

#endif // TILE_LOADER
