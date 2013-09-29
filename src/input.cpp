// input.cpp
//
// 
// Description:
//
//////////////////////////////////////////////////////////////////////

#include "input.h"

using namespace blueprint;

Input::Input()
{
    init();
}

Input::~Input()
{
    
}

void Input::init()
{
    MEVENT event;
    keypad(stdscr, TRUE);
    noecho();
    // Hide the cursor ( until moving it )
    curs_set( 0 );
    // Get all the mouse events
    mousemask(ALL_MOUSE_EVENTS, NULL);
    int ch;
    bool exit_loop = false;
    while ( true ) {
        if ( ( ch = getch() ) == ERR) {  // Hang around while I work on stuff
            
        } else
        {
            switch ( ch )
            {
            case KEY_MOUSE:
            {
                if ( getmouse( &event ) == OK) {
                    if ( event.bstate & BUTTON1_PRESSED ) {
                        LOG(INFO) << "Mouse button 1 pressed.";            
                    }
                } 
                break;
            }
            case KEY_F(1):
            {
                exit_loop = true;
                break;
            }
            case KEY_UP:
            {
                move_cursor_up( );
                break;
            }
            case KEY_DOWN:
            {
                move_cursor_down( );
                break;
            }
            case KEY_LEFT:
            {
                move_cursor_left( );
                break;
            }
            case KEY_RIGHT:
            {
                move_cursor_right( );
                break;
            }
            }
        }
        if (exit_loop == true) {
            break;
        }
    }
}

// Cursor handling

bool Input::move_cursor_left()
{
    return true;
}

bool Input::move_cursor_right()
{
    return true;
}

bool Input::move_cursor_up()
{
    return true;
}

bool Input::move_cursor_down()
{
    return true;
}

// Window callback

void Input::set_current_window( WINDOW* active_window )
{
    m_active_window = active_window;
}
