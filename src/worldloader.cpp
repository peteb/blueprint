
// own
#include "worldloader.h"

// std
#include <cassert>

using namespace VW;

void WorldLoader::setup_map( int32 map_x_size, int32 map_y_size,
                             uint32 tile_size, uint32 chunk_size )
{
    assert( map_x_size != 0 && map_y_size != 0 && tile_size != 0 && chunk_size != 0 );
    m_mapdata.mapx = map_x_size;
    m_mapdata.mapy = map_y_size;
    m_mapdata.tile_size = tile_size;
    m_mapdata.chunk_size = chunk_size;
    m_mapdata.chunks_x = map_x_size / chunk_size;
    m_mapdata.chunks_y = map_y_size / chunk_size;
}

/*

Say x = 0; and y = 0;

First vertex position will be:
    0, 0
Second will be:
    32, 0
Third will be:
    32, 32
Fourth will be:
    0, 32

Essentially a quad will be drawn counter-clockwise.
*/
void WorldLoader::append_tile( uint32 x, uint32 y, sf::VertexArray& vertex_array )
{
    sf::Vertex ver;
    // upper left
    ver.position = sf::Vector2f( x * m_mapdata.tile_size, y * m_mapdata.tile_size );
    ver.texCoords = sf::Vector2f( 0.f, 0.f );
    vertex_array.append( ver );

    // lower left
    ver.position = sf::Vector2f( x * m_mapdata.tile_size + m_mapdata.tile_size,
                                 y * m_mapdata.tile_size );
    ver.texCoords = sf::Vector2f( m_mapdata.tile_size, 0.f );
    vertex_array.append( ver );

    // lower right
    ver.position = sf::Vector2f( x * m_mapdata.tile_size + m_mapdata.tile_size,
                                 y * m_mapdata.tile_size + m_mapdata.tile_size );
    ver.texCoords = sf::Vector2f( m_mapdata.tile_size, m_mapdata.tile_size );
    vertex_array.append( ver );

    // upper right
    ver.position = sf::Vector2f(x * m_mapdata.tile_size, y * m_mapdata.tile_size + m_mapdata.tile_size );
    ver.texCoords = sf::Vector2f( 0.f, m_mapdata.tile_size );
    vertex_array.append( ver );
}

void WorldLoader::create_world_chunk( uint32 chunk_x_pos, uint32 chunk_y_pos, uint32 chunk_size )
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
    height_map_builder.SetDestSize( m_mapdata.mapx * m_mapdata.tile_size,
                                    m_mapdata.mapy * m_mapdata.tile_size );
    height_map_builder.SetBounds( chunk_x_pos, chunk_x_pos + CHUNK_SCALE, chunk_y_pos,
                                  chunk_y_pos + CHUNK_SCALE );
    height_map_builder.Build( );

    // Build array of values
//    for ( uint32 cy = 0; cy < m_mapdata.mapy / chunk_size; cy++ ) {
//        for ( uint32 cx = 0; cx < m_mapdata.mapx / chunk_size ; cx++ ) {
//            for ( uint32 ty = 0; ty < m_mapdata.tile_size; ty++ ) {
//                for ( uint32 tx = 0; tx < m_mapdata.tile_size; tx++ ) {
//                    height_map.GetValue( ( ( ( cy * cx + cx) * m_mapdata.tile_size ) + ( ty * tx + tx ) ) );
//                }
//            }
//            height_map.GetValue()
//        }
//    }

    snapshot( height_map );
}

const sf::Texture& WorldLoader::get_tilemap_texture( ) const
{
    return m_mapdata.m_textures.get( Textures::Landscape );
}

void WorldLoader::snapshot( utils::NoiseMap& height_map )
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

