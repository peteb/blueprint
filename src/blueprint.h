#ifndef _BLUEPRINT_H_
#define _BLUEPRINT_H_

//own
#include "voidworld.h"

// SFML (Simple and Fast Multimedia Library)
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

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

        VW::VoidWorld world;
    };   
}

#endif // BLUEPRINT_H


