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

class noise::utils::GradientColor;
class WorldLoader : public TileLoader
{
public:

    const float TILE_SIZE = 64.f;

    WorldLoader( void )
    {
        // Set the noise parameters

        m_ridge.SetSeed( m_seed );
        m_ridge.SetLacunarity( 0.5 );
        m_ridge.SetFrequency( 3.0 );
        m_ridge.SetOctaveCount( 5 );

        m_turbulence.SetSourceModule( 0, m_ridge );
        m_turbulence.SetFrequency( 2.0 );
        m_turbulence.SetPower( 0.5 );

        m_mapdata.mapx = 100;
        m_mapdata.mapy = 100;
        m_mapdata.texture_name="tileset1.tga";
    }

    void create_spherical_world()
    {
        module::RidgedMulti mountainTerrain;
        mountainTerrain.SetFrequency( 1 );
        mountainTerrain.SetLacunarity( 2 );
        mountainTerrain.SetOctaveCount( 2 );
        module::Billow baseFlatTerrain;
        baseFlatTerrain.SetFrequency (2.0);
        baseFlatTerrain.SetOctaveCount( 1 );
        module::ScaleBias flatTerrain;
        flatTerrain.SetSourceModule (0, baseFlatTerrain);
        flatTerrain.SetScale ( 0.2 );
        flatTerrain.SetBias( 0.2 );

        module::Perlin terrainType;
        terrainType.SetFrequency ( 1 );
        terrainType.SetPersistence (0.55);
        terrainType.SetOctaveCount( 2 );
        terrainType.SetLacunarity( 0.9 );
        module::Select terrainSelector;
        terrainSelector.SetSourceModule (0, flatTerrain);
        terrainSelector.SetSourceModule (1, mountainTerrain);
        terrainSelector.SetControlModule (terrainType);
        terrainSelector.SetBounds (0.0, 1000.0);
        terrainSelector.SetEdgeFalloff (0.35);

        module::Turbulence finalTerrain;
        finalTerrain.SetSourceModule (0, terrainSelector);
        finalTerrain.SetFrequency (4.0);
        finalTerrain.SetPower (0.125);

        utils::NoiseMap heightMap;
        utils::NoiseMapBuilderPlane heightMapBuilder;
        heightMapBuilder.SetSourceModule (finalTerrain);
        heightMapBuilder.SetDestNoiseMap (heightMap);
        heightMapBuilder.SetDestSize (512, 512);
        heightMapBuilder.SetBounds (6.0, 12.0, 1.0, 7.0);
        heightMapBuilder.Build ();

        utils::RendererImage renderer;
        utils::Image image;
        renderer.SetSourceNoiseMap (heightMap);
        renderer.SetDestImage (image);
        renderer.ClearGradient ();
        renderer.AddGradientPoint (-1.0000, utils::Color (  0,   0, 128, 255)); // deeps
        renderer.AddGradientPoint (-0.3500, utils::Color (  0,   0, 255, 255)); // shallow
        renderer.AddGradientPoint ( 0.0000, utils::Color (  0, 128, 255, 255)); // shore
        renderer.AddGradientPoint ( 0.0625, utils::Color (240, 240,  64, 255)); // sand
        renderer.AddGradientPoint ( 0.1250, utils::Color ( 32, 160,   0, 255)); // grass
        renderer.AddGradientPoint ( 0.3750, utils::Color (224, 224,   0, 255)); // dirt
        renderer.AddGradientPoint ( 0.7500, utils::Color (128, 128, 128, 255)); // rock
        renderer.AddGradientPoint ( 1.0000, utils::Color (255, 255, 255, 255)); // snow
        renderer.Render ();

        utils::WriterBMP writer;
        writer.SetSourceImage (image);
        writer.SetDestFilename ("world.bmp");
        writer.WriteDestFile ();

        snapshot();
    }

    void snapshot()
    {
        utils::NoiseMap height_map;
        utils::NoiseMapBuilderPlane height_map_builder;
        height_map_builder.SetSourceModule( m_turbulence );
        height_map_builder.SetDestNoiseMap( height_map );
        height_map_builder.SetDestSize( 512, 512 );
        height_map_builder.SetBounds( 6.0, 10.0, 1.0, 5.0 );
        height_map_builder.Build( );
        
        
        utils::RendererImage renderer;
        utils::Image image;
        renderer.SetSourceNoiseMap( height_map );
        renderer.SetDestImage( image );
        
        renderer.Render();
        
        utils::WriterBMP writer;
        writer.SetSourceImage( image );
        writer.SetDestFilename( "snapshot.bmp" );
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
    noise::module::Perlin m_perlin;
    noise::module::RidgedMulti m_ridge;
    noise::module::Turbulence m_turbulence;
};
