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

using namespace blueprint;

//-------------------------------------------------------------------------------------------------

WorldView::WorldView()
{
    init( );
} 

//-------------------------------------------------------------------------------------------------

WorldView::~WorldView()
{
    LOG ( INFO ) << "WorldView exiting";
    endwin( );
}

//-------------------------------------------------------------------------------------------------

void WorldView::init( )
{
}

//------------------------------------------------------------------------------------------------

void WorldView::create_fullterminal_panel( const char* panel_name, bool border, bool hidden )
{
    int x = 0;
    int y = 0;
    getmaxyx( stdscr, y, x );
    DLOG( INFO ) << "Screen width " << x << " Screen height " << y;
    create_panel( panel_name, 0, 0, y, x , border, hidden );
}

// -------------------------------------------------------------------------------------------------

// Panels are always tied to windows.
// Therefor with this implementation, the window size will always be the same as that of the panel.
bool WorldView::create_panel( const char* panel_name, int startx,
                              int starty, int lines, int columns, bool border, bool hidden)
{
    // Create panel info class
    PanelInfo* panel_info = new PanelInfo;

    // Create window
    WINDOW* win = newwin(lines, columns, starty, startx);
    if ( win == NULL ) {
        LOG( ERROR ) << "Unable to create ncurses window.";
        return false;
    }
    panel_info->window_info.window = win;
    panel_info->window_info.border = border;
    panel_info->window_info.lines = lines;
    panel_info->window_info.columns = columns;
    panel_info->window_info.starty = starty;
    panel_info->window_info.startx = startx;
    
    if ( border ) {
        box( win, 0, 0 );
    }
    wrefresh( win );

    // Create panel
    PANEL* panel = new_panel( win );
    if ( panel == NULL ) {
        LOG( ERROR ) << "Unable to create ncurses panel.";
        return false;
    }
    panel_info->panel = panel;
    panel_info->hidden = hidden;
    
    std::shared_ptr<PanelInfo> p(new PanelInfo);
    // Add to the the map of panels
    std::string name( panel_name );
    if ( ! m_panels.insert( std::make_pair( panel_name, p ) ).second ) {
        LOG( WARNING ) << "Unable to add panel, name already exist.";
        return false;
    }
    update_panels();
    return true;
}

//-------------------------------------------------------------------------------------------------

