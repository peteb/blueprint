#ifndef _BLUEPRINT_H_
#define _BLUEPRINT_H_

//own
#include "voidworld.h"
#include "worldmap.h"

// SFML (Simple and Fast Multimedia Library)
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

// The game class

namespace blueprint
{   
    class Blueprint
    {
    public:
        Blueprint( );
        ~Blueprint( );

        void init( );
        void run( );
    private:
        void process_events ();
        void handlePlayerInput( sf::Keyboard::Key key, bool is_pressed );

        void update( );
        void render( );
    private:
        sf::RenderWindow m_win;
        sf::Time m_time_per_frame;
        sf::View m_camera;
        VW::WorldMap m_worldmap;
    };
} // namespace blueprint

#endif // BLUEPRINT_H


