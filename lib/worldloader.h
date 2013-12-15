#include "tileloader.h"
#include "statictilemap.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <libnoise/noise.h>
#include "noiseutils.h"
#include "tileloader.h"
#include "statictilemap.h"
#include <cstdint>

namespace vw
{

class WorldLoader : public vm::TileLoader
{
public:

    const float TILE_SIZE = 64.f;
    const int CHUNK_AREA = 3;

    WorldLoader( void )
    {
        m_mapdata.texture_name = "resources/tilesets/tileset1.tga";
    }

    void create_world_chunk( u_int32_t chunk_x_pos, u_int32_t chunk_y_pos, u_int32_t chunk_size )
    {
        module::RidgedMulti mountain_terrain;
        mountain_terrain.SetFrequency( 0.3 );
        mountain_terrain.SetOctaveCount( 10 );
        module::Billow base_flat_terrain;
        base_flat_terrain.SetFrequency( 0.3 );
        base_flat_terrain.SetPersistence( 0.5 );

        module::ScaleBias flat_terrain;
        flat_terrain.SetSourceModule( 0, base_flat_terrain );
        flat_terrain.SetScale( 0 );
        flat_terrain.SetBias( 0.15 );

        module::Perlin terrain_type;
        terrain_type.SetFrequency( 1.6 );
        terrain_type.SetPersistence( 0.25 );
        terrain_type.SetLacunarity( 2 );
        terrain_type.SetOctaveCount( 12 );

        module::Select terrain_selector;
        terrain_selector.SetSourceModule( 0, flat_terrain);
        terrain_selector.SetSourceModule( 1, mountain_terrain );
        terrain_selector.SetControlModule( terrain_type );
        terrain_selector.SetBounds( 0.0, 1000.0 );
        terrain_selector.SetEdgeFalloff( 0.5 );

        module::Turbulence final_terrain;
        final_terrain.SetPower( 0.13 );
        final_terrain.SetRoughness( 2 );
        final_terrain.SetSourceModule (0, terrain_selector);

        utils::NoiseMap height_map;
        utils::NoiseMapBuilderPlane height_map_builder;
        height_map_builder.SetSourceModule( final_terrain );
        height_map_builder.SetDestNoiseMap( height_map );
        height_map_builder.SetDestSize( chunk_size, chunk_size );
        height_map_builder.SetBounds( chunk_x_pos, chunk_x_pos + CHUNK_AREA, chunk_y_pos,
                                      chunk_y_pos + CHUNK_AREA );
        height_map_builder.Build( );

        // Build array of values
        for ( u_int32_t i = 0; i < chunk_size; i++ ) {
            for ( u_int32_t j = 0; j < chunk_size ; j++ ) {
                
            }
        }
        height_map.GetValue(0, 0);
        
        snapshot( height_map );

    }

    void snapshot( utils::NoiseMap& height_map )
    {
        utils::RendererImage renderer;
        utils::Image image;
        renderer.SetSourceNoiseMap( height_map );
        renderer.SetDestImage ( image );
        renderer.ClearGradient( );
        renderer.AddGradientPoint(-1.0000, utils::Color( 0, 0, 128, 255 ) ); // deeps
        renderer.AddGradientPoint(-0.2500, utils::Color( 0, 0, 255, 255 ) ); // shallow
        renderer.AddGradientPoint( 0.0000, utils::Color( 0, 128, 255, 255 ) ); // shore
        renderer.AddGradientPoint( 0.0625, utils::Color( 240, 240,  64, 255 ) ); // sand

        renderer.AddGradientPoint( 0.1250, utils::Color( 32, 160, 0, 255  ) ); // grass
        renderer.AddGradientPoint( 0.2150, utils::Color( 0, 100, 0, 255  ) ); // trees
        renderer.AddGradientPoint( 0.3750, utils::Color( 224, 224, 0, 255 ) ); // dirt
        renderer.AddGradientPoint( 0.7500, utils::Color( 128, 128, 128, 255 ) ); // rock
        renderer.AddGradientPoint( 1.0000, utils::Color( 255, 255, 255, 255 ) ); // snow

        renderer.Render( );

        utils::WriterBMP writer;
        writer.SetSourceImage( image );
        writer.SetDestFilename( "world.bmp" );
        writer.WriteDestFile( );
    }

    virtual void append_tile( u_int32_t gx, u_int32_t gy, sf::VertexArray& garr )
    {
        sf::Vertex ver;
        ver.position = sf::Vector2f( gx * TILE_SIZE, gy * TILE_SIZE );
        ver.texCoords = sf::Vector2f( 0.f, 0.f );
        garr.append( ver );
        
        ver.position = sf::Vector2f( gx * TILE_SIZE + TILE_SIZE, gy * TILE_SIZE );
        ver.texCoords = sf::Vector2f( TILE_SIZE, 0.f );
        garr.append( ver );
        
        ver.position = sf::Vector2f( gx * TILE_SIZE + TILE_SIZE, gy * TILE_SIZE + TILE_SIZE );
        ver.texCoords = sf::Vector2f( TILE_SIZE, TILE_SIZE );
        garr.append( ver );
        
        ver.position = sf::Vector2f(gx * TILE_SIZE, gy * TILE_SIZE + TILE_SIZE );
        ver.texCoords = sf::Vector2f( 0.f, TILE_SIZE );
        garr.append( ver );
    }

private:
    int m_seed;
};

} // namespace vw
