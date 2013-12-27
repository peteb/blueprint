
// own
#include "worldloader.h"
#include "common.h"

// std
#include <cassert>

using namespace VW;

void WorldLoader::setup_map( int32 map_x_size, int32 map_y_size,
                             uint32 tile_size, uint32 chunk_size )
{
    assert( map_x_size != 0 && map_y_size != 0 && tile_size != 0 && chunk_size != 0 );
    m_mapdata.m_mapx = map_x_size;
    m_mapdata.m_mapy = map_y_size;
    m_mapdata.m_tile_size = tile_size;
    m_mapdata.m_chunk_size = chunk_size;
    m_mapdata.m_chunks_x = map_x_size / chunk_size;
    m_mapdata.m_chunks_y = map_y_size / chunk_size;
    create_world_chunk( 0, 0, chunk_size );
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

Grab the proper texture coordinates for the image to be shown.

*/
void WorldLoader::append_tile( uint32 x, uint32 y, sf::VertexArray& vertex_array )
{
    // Get the landscape tile at x, y
    uint32 tx_offset = 0;
    uint32 ty_offset = 0;
    get_texture_tile_offsets( x, y, tx_offset, ty_offset );

    sf::Vertex ver;
    // upper left
    ver.position = sf::Vector2f( x * m_mapdata.m_tile_size,
                                 y * m_mapdata.m_tile_size );
    ver.texCoords = sf::Vector2f( tx_offset + 0.f, ty_offset + 0.f );
    vertex_array.append( ver );

    // lower left
    ver.position = sf::Vector2f( x * m_mapdata.m_tile_size + m_mapdata.m_tile_size,
                                 y * m_mapdata.m_tile_size );
    ver.texCoords = sf::Vector2f( tx_offset + m_mapdata.m_tile_size, ty_offset + 0.f );
    vertex_array.append( ver );

    // lower right
    ver.position = sf::Vector2f( x * m_mapdata.m_tile_size + m_mapdata.m_tile_size,
                                 y * m_mapdata.m_tile_size + m_mapdata.m_tile_size );
    ver.texCoords = sf::Vector2f( tx_offset + m_mapdata.m_tile_size, ty_offset + m_mapdata.m_tile_size );
    vertex_array.append( ver );

    // upper right
    ver.position = sf::Vector2f(x * m_mapdata.m_tile_size,
                                y * m_mapdata.m_tile_size + m_mapdata.m_tile_size );
    ver.texCoords = sf::Vector2f( tx_offset + 0.f, ty_offset + m_mapdata.m_tile_size );
    vertex_array.append( ver );
}

void WorldLoader::get_texture_tile_offsets( const uint32 x, const uint32 y,
                                            uint32& tx_offset, uint32& ty_offset )
{
    // Find out if chunks needs to be generated
    // If so check that they do not exist already.
    // Chunks are stored on disk, depending on the position of the user
    auto it = m_mapdata.m_chunk_ids[ 0 ];
    assert( it.size() > m_mapdata.m_tile_size * y + x );
    TerrainTypes type = static_cast< TerrainTypes >( it[ m_mapdata.m_tile_size * y + x ] - 1 );

    // Now pick the tile to use
    // TODO: Fix so that that several tiles of the same type may exist, for variation.
    switch ( type )
    {
    case TerrainTypes::DEEP_WATER:
        // Tile 0
        tx_offset = 0;
        ty_offset = 0;
        break;
    case TerrainTypes::WATER:
        // Tile 1
        tx_offset = m_mapdata.m_tile_size * 1;
        ty_offset = 0;
        break;
    case TerrainTypes::BEACH:
        // Tile 2
        tx_offset = m_mapdata.m_tile_size * 2;
        ty_offset = 0;
        break;
    case TerrainTypes::SAND:
        // Tile 3
        tx_offset = m_mapdata.m_tile_size * 3;
        ty_offset = 0;
        break;
    case TerrainTypes::GRASS:
        // Tile 4
        tx_offset = m_mapdata.m_tile_size * 4;
        ty_offset = 0;
        break;
    case TerrainTypes::FOREST:
        tx_offset = m_mapdata.m_tile_size * 5;
        ty_offset = 0;
        break;
    case TerrainTypes::TUNDRA:
        tx_offset = m_mapdata.m_tile_size * 6;
        ty_offset = 0;
        break;
    case TerrainTypes::ROCK:
        tx_offset = m_mapdata.m_tile_size * 7;
        ty_offset = 0;
        break;
    case TerrainTypes::MOUNTAIN:
        tx_offset = m_mapdata.m_tile_size * 8;
        ty_offset = 0;
        break;
    default:
        //assert( !"Invalid terrain" );
        break;
    }
}

uint32 WorldLoader::clamp_height_to_terrain( uint32 height )
{
    return height / TERRAIN_TYPES;
}

// Create a chunk, using the current view position
void WorldLoader::get_heights( utils::NoiseMap& height_map, std::vector< uint32 >& height_values )
{
    for ( uint32 cy = 0; cy < m_mapdata.m_tile_size; cy++ ) {
        for ( uint32 cx = 0; cx < m_mapdata.m_tile_size ; cx++ ) {
            uint32 height = static_cast< uint32 >( height_map.GetValue( cx, cy ) * 100 );
            if ( height > 100 ) {
                height = 100;
            }
            // Render the area
            height_values.push_back( clamp_height_to_terrain( height ) );
        }
    }
}

uint64 WorldLoader::create_64bit_id( uint32 chunk_x_pos, uint32 chunk_y_pos )
{
    uint64 id = 0;
    id = chunk_x_pos;
    id = id << 32;
    id |= chunk_y_pos;
    return id;
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
    height_map_builder.SetDestSize( m_mapdata.m_tile_size,
                                    m_mapdata.m_tile_size );
    height_map_builder.SetBounds( chunk_x_pos, chunk_x_pos + 1, chunk_y_pos,
                                  chunk_y_pos + 1 );
    height_map_builder.Build( );

    //TODO: Create unique values out of the chunk positions
    // Load an area around the view using current viewsize vs tilesize and preload / create chunks,
    // which will be saved to disk if they are dirty

    // Build the id
    uint64 id = create_64bit_id( chunk_x_pos, chunk_y_pos );

    // Check if it exists already
    if ( auto it = m_mapdata.m_chunk_ids.find( id ) != m_mapdata.m_chunk_ids.end( ) ) {
        // Value exists, use it

    } else {
        // Create new chunk
        MapData::MapHeights map_chunk;
        get_heights( height_map, map_chunk );
        m_mapdata.m_chunk_ids.insert( std::make_pair( id, map_chunk ) );
    }

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

    renderer.AddGradientPoint( -1.0000, utils::Color( 0, 0, 128, 255 ) ); // deeps
    renderer.AddGradientPoint( -0.7500, utils::Color( 0, 0, 255, 255 ) ); // shallow
    renderer.AddGradientPoint( -0.50000, utils::Color( 0, 128, 255, 255 ) ); // shore
    renderer.AddGradientPoint( -0.25, utils::Color( 240, 240,  64, 255 ) ); // sand
    renderer.AddGradientPoint( 0.0, utils::Color( 32, 160, 0, 255  ) ); // grass
    renderer.AddGradientPoint( 0.25, utils::Color( 0, 100, 0, 255  ) ); // trees
    renderer.AddGradientPoint( 0.50, utils::Color( 224, 224, 0, 255 ) ); // dirt
    renderer.AddGradientPoint( 0.75, utils::Color( 128, 128, 128, 255 ) ); // rock
    renderer.AddGradientPoint( 1.0000, utils::Color( 255, 255, 255, 255 ) ); // snow

    renderer.Render( );

    utils::WriterBMP writer;
    writer.SetSourceImage( image );
    writer.SetDestFilename( "world.bmp" );
    writer.WriteDestFile( );
}

