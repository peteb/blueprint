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
    typedef uint64 ChunkId;
    typedef std::vector< uint32 > MapHeights;
    TextureHolder m_textures;
    uint32 m_mapx = 0;
    uint32 m_mapy = 0;
    uint32 m_tile_size = 0;
    uint32 m_chunk_size = 0;
    uint32 m_chunks_x = 0;
    uint32 m_chunks_y = 0;
    std::map< ChunkId, MapHeights > m_chunk_ids;
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
