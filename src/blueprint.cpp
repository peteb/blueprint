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
    : m_win(sf::VideoMode(640,480), "Blueprint")
{
}

//--------------------------------------------------------------------

Blueprint::~Blueprint()
{
}

//--------------------------------------------------------------------

void Blueprint::run()
{
    while ( m_win.isOpen( ) )
    {
        process_events( );
        m_win.clear();
        //m_win.draw(shape);
        m_win.display();
    }    
}

//--------------------------------------------------------------------

void Blueprint::process_events( )
{
    sf::Event event;
    while ( m_win.pollEvent( event ) )
    {
        if ( event.type == sf::Event::Closed ) {
            m_win.close( );
        }
    }
}

//--------------------------------------------------------------------

void Blueprint::update()
{
}

//--------------------------------------------------------------------

void Blueprint::render()
{
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
    b.run();

    
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

