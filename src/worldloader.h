#ifndef WORLD_LOADER_H
#define WORLD_LOADER_H

// own
#include "common.h"
#include "tileloader.h"
#include "noiseutils.h"
#include "tileloader.h"
#include "textureholder.h"

// sfml
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

// libnoise
#include <libnoise/noise.h>


namespace VW
{

class WorldLoader : public TileLoader
{
public:
    static const uint32 CHUNK_SCALE = 3;
    WorldLoader( )
    {
        m_mapdata.mapx = 0;
        m_mapdata.mapy = 0;
        m_mapdata.tile_size = 0;
        m_mapdata.chunk_size = 0;
    }
    ~WorldLoader( ) { }
    void setup_map( int32 map_x_size, int32 map_y_size, uint32 tile_size, uint32 chunk_size );

    // override
    void append_tile( uint32 x, uint32 y, sf::VertexArray& vertex_array );

    void create_world_chunk( uint32 chunk_x_pos, uint32 chunk_y_pos, uint32 m_chunk_size );
    const sf::Texture& get_tilemap_texture() const;
    void get_texture_tile_offsets(uint32& tx_offset, uint32& ty_offset );
    void snapshot( utils::NoiseMap& height_map );

private:
    int m_seed;
};

} // namespace vw

#endif // _WORLD_LOADER_H_
