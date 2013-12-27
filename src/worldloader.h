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

// std
#include <vector>

namespace VW
{

class WorldLoader : public TileLoader
{
public:
    WorldLoader( )
    {
        m_mapdata.m_mapx = 0;
        m_mapdata.m_mapy = 0;
        m_mapdata.m_tile_size = 0;
        m_mapdata.m_chunk_size = 0;
    }
    ~WorldLoader( ) { }

    enum class TerrainTypes : uint8 {
        DEEP_WATER,
        WATER,
        BEACH,
        SAND,
        GRASS,
        FOREST,
        TUNDRA,
        ROCK,
        MOUNTAIN,
        TERRAIN_TYPES_MAX
    };
    static const uint32
    TERRAIN_TYPES = 100 /
            static_cast< uint32 >(TerrainTypes::TERRAIN_TYPES_MAX );

    void setup_map( int32 map_x_size, int32 map_y_size, uint32 tile_size, uint32 chunk_size );

    // override
    void append_tile( uint32 x, uint32 y, sf::VertexArray& vertex_array );

    void create_world_chunk( uint32 chunk_x_pos, uint32 chunk_y_pos, uint32 m_chunk_size );
    const sf::Texture& get_tilemap_texture() const;
    void get_texture_tile_offsets( const uint32 x, const uint32 y,
                                   uint32& tx_offset, uint32& ty_offset );
    ///
    /// \brief clamp_height_value Clamps the value to the predifined ranges used
    /// \param height int
    /// \return new clamped value
    ///
    uint32 clamp_height_to_terrain( uint32 height );
    void snapshot( utils::NoiseMap& height_map );

    void get_heights( utils::NoiseMap& height_map, std::vector<uint32>& height_values );
    uint64 create_64bit_id( uint32 chunk_x_pos, uint32 chunk_y_pos );
private:
    int m_seed;
};

} // namespace vw

#endif // _WORLD_LOADER_H_
