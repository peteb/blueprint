#ifndef _BLUEPRINT_H_
#define _BLUEPRINT_H_

// SFML (Simple and Fast Multimedia Library)
#include <SFML/Graphics.hpp>

// The game class

namespace blueprint
{   
    class Blueprint
    {
    public:
        Blueprint();
        ~Blueprint();
        void run();
    private:
        void process_events();
        void update();
        void render();
    private:
        sf::RenderWindow m_win;
    };   
}

#endif // BLUEPRINT_H


