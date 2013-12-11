#include "TileLoader.h"
#include "statictiledmap.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

class WorldLoader : public TileLoader
{
public:

    const static float TILE_SIZE = 64.f;

    WorldLoader( void )
    {
        m_mapdata.map_x = 100;
        m_mapdata.map_y =100;
        m_mapdata.texture_name="tileset1.tga";
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
};
