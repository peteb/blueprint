// screen.cpp
//
// 
// Description:
//
//////////////////////////////////////////////////////////////////////

#include "world_view.h"

// NCurses
#include <ncurses.h>
#include <panel.h>

#include <glog/logging.h>

using namespace blueprint;

//-------------------------------------------------------------------------------------------------

WorldView::WorldView()
{
    init();
} 

//-------------------------------------------------------------------------------------------------

WorldView::~WorldView()
{
}

//-------------------------------------------------------------------------------------------------

void WorldView::init( )
{
    initscr( );
    start_color( );
    raw( );
}

//-------------------------------------------------------------------------------------------------

void WorldView::cleanup( )
{
}


//------------------------------------------------------------------------------------------------

void WorldView::create_fullterminal_panel( std::string& panel_name, bool border, bool hidden )
{
    int x = 0;
    int y = 0;
    getmaxyx( stdscr, y, x );
    DLOG( INFO ) << "Screen width " << x << " Screen height " << y;
    create_panel( panel_name, x, y );
}

// -------------------------------------------------------------------------------------------------

void WorldView::create_panel( int x, int y, int width, int height, bool border, bool hidden )
{
}

// -------------------------------------------------------------------------------------------------

PANEL* WorldView::create_panel( std::string& panel_name, int x, int y )
{
    WINDOW* win = newwin(0, 0, 0, 0); // Fullscreen
    PANEL* p = new_panel(win);
    // TODO: Attach a shared_pointer with a deleter function to free the memory of the panel and window
}

//-------------------------------------------------------------------------------------------------

