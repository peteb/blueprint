// -------------------------------------------------------------------------------------------------
//
// Blueprint
//
// -------------------------------------------------------------------------------------------------

#include "blueprint.h"
#include "voidworld.h"

#include <glog/logging.h>

#include <iostream>

using namespace blueprint;

//-| Blueprint class |------------------------------------------------

Blueprint::Blueprint( )
    : m_win( sf::VideoMode( 640,480 ), "Blueprint" )
    , m_time_per_frame(sf::seconds( 1.0f / 60.0f ) )

{
    m_win.setVerticalSyncEnabled( true );
    m_camera = m_win.getDefaultView( );
    init( );
    run( );
}

void Blueprint::init( )
{
    std::string tileset("../resources/tilesets/test_tileset.tga");
    m_worldmap.setup_map( 10, 10, 32, 32, tileset );
}

//--------------------------------------------------------------------

Blueprint::~Blueprint( )
{
    DLOG( INFO ) << "Blueprint exiting";
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
        case sf::Event::Resized:
        {
            // Update the view to the new size of the window
            sf::FloatRect visible_area(0, 0, event.size.width, event.size.height);
            m_win.setView( sf::View( visible_area ) );
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
    if ( key == sf::Keyboard::Q ) {
        m_camera.zoom( 1.05f );
    }
    if ( key == sf::Keyboard::W ) {
        m_camera.move( 0.f, -10.f );
    }
    if ( key == sf::Keyboard::E ) {
        m_camera.zoom( 0.95f );
    }

    if( key == sf::Keyboard::A ) {
        m_camera.move( -10.f, 0.f );
    }
    if ( key == sf::Keyboard::S ) {
        m_camera.move( 0.f, 10.f );
    }

    if ( key == sf::Keyboard::D ) {
        m_camera.move( 10.f, 0.f );
    }

    if ( key == sf::Keyboard::Escape ) {
        m_win.close();
    }
}             

//--------------------------------------------------------------------
// Update updates the gamestate and moves things around etc.
void Blueprint::update( )
{
    
}

//--------------------------------------------------------------------

void Blueprint::render()
{
    m_win.setView( m_camera );
    m_win.clear();
    m_win.draw( m_worldmap );
    m_win.display();
}

//--------------------------------------------------------------------

// The one and only main method

int main( int argc, char* argv[] )
{
    // Initialize google logging
    google::InitGoogleLogging( argv[0] );
    FLAGS_logtostderr = 1;
    DLOG( INFO ) << "Starting Blueprint";

    // Start everything
//    try {
    Blueprint blueprint;
//    } catch (...)
//    {
//        DLOG( ERROR ) << "Caught undefined exception";
//    }

    return 0;
}

