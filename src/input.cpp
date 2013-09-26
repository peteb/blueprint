// input.cpp
//
// 
// Description:
//
//////////////////////////////////////////////////////////////////////

#include "input.h"

using namespace voids;

Input::Input()
{
    
}

Input::~Input()
{
    
}

void Input::init()
{

}

void Input::cleanup()
{

}

// Cursor handling

bool Input::move_cursor_left()
{
}

bool Input::move_cursor_right()
{
}

bool Input::move_cursor_up()
{
}

bool Input::move_cursor_down()
{
}

// Window callback

void Input::set_current_window( WINDOW* active_window )
{
    m_active_window = active_window;
}
