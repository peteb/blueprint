// -------------------------------------------------------------------------------------------------
//
// Blueprint
//
// -------------------------------------------------------------------------------------------------

#include "blueprint.h"

#include "voidworld.h"
#include "world_view.h"
#include "input.h"

#include <ncurses.h>

#include <glog/logging.h>

#include <iostream>

using namespace blueprint;

static std::string testmap = { // x:52, y:17
    "#####################################################"
    "#                                                   #"
    "#                                                   #"
    "#       ####    #    ##         #                   #"
    "#               #   # #         #                   #"
    "#       #      ##   #    ###    #                   #"
    "#       #           #      ######                   #"
    "#  ######               ##                #         #"
    "#                                         #         #"
    "#                       @                 #         #"
    "#                                                   #"
    "#                                                   #"
    "#                                                   #"
    "#                ## # # ##### #    #####            #"
    "#                                      #            #"
    "#                                      #            #"
    "#                                      #            #"
    "#####################################################"
};

//-| Blueprint class |------------------------------------------------

Blueprint::Blueprint()
    : m_win( sf::VideoMode( 640,480 ), "Blueprint" )
    , m_time_per_frame(sf::seconds( 1.0f / 60.0f ) )

{
    run();
}

//--------------------------------------------------------------------

Blueprint::~Blueprint( )
{
}

//--------------------------------------------------------------------

void Blueprint::run( )
{
    sf::Clock clock;
    sf::Time time_since_last_update = sf::Time::Zero;
    while ( m_win.isOpen( ) )
    {
        process_events( );
        time_since_last_update += clock.restart();
        while ( time_since_last_update > m_time_per_frame ) {
            time_since_last_update -= m_time_per_frame;
            process_events( );
            update( );
        }
        render( );
    }    
}

//--------------------------------------------------------------------

void Blueprint::process_events( )
{
    sf::Event event;
    while ( m_win.pollEvent( event ) )
    {
        switch ( event.type )
        {
            case sf::Event::KeyPressed:
            {
                handlePlayerInput( event.key.code, true );
                break;
            }
            case sf::Event::KeyReleased:
            {
                handlePlayerInput(event.key.code, false );
                break;
            }
            case sf::Event::Closed:
            {
                m_win.close( );
                break;
            }
            default:
                break;
        }
    }
}

//--------------------------------------------------------------------

void Blueprint::handlePlayerInput( sf::Keyboard::Key key, bool is_pressed )
{
    //if (key == sf::Keyboard::W)
    //    mIsMovingUp = isPressed;

}             

//--------------------------------------------------------------------
// Update updates the gamestate and moves things around etc.
void Blueprint::update( )
{
    
}

//--------------------------------------------------------------------

void Blueprint::render()
{
        m_win.clear( );
        //m_win.draw(shape);
        m_win.display( );
}

//--------------------------------------------------------------------

// The one and only main method

int main( int argc, char* argv[] )
{
    // Initialize google logging
    google::InitGoogleLogging( argv[0] );
    FLAGS_logtostderr = 1;
    DLOG( INFO ) << " Starting Blueprint ";

    // Initializing OpenGL
    Blueprint b;

    
//    initscr( );
//    if ( has_colors() == FALSE ) {
//        LOG(WARNING) << "Your terminal lacks colors.";
//    } else {
//        start_color( );
//    }
//    init_pair( 1, COLOR_RED, COLOR_BLACK );
//    attron( COLOR_PAIR( 1 ) );
    // Setting up the world

    //WorldView wv;
    //wv.create_fullterminal_panel( "Main", true, false );

    //Input input;
    vw::VoidWorld world;
    world.set_data_source( testmap.c_str(), 53, 18 );
    world.update_entity_position( 25, 9 );

    return 0;
}

