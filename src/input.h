// input.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef INPUT_H
#define INPUT_H 1

#include <ncurses.h>

namespace voids
{
    class Input
{
public:
    Input();
    ~Input();
    void init();
    void cleanup();
    
// Cursor movement
    
    bool move_cursor_left();
    bool move_cursor_right();
    bool move_cursor_up();
    bool move_cursor_down();
    
// Window callback
    void set_current_window( WINDOW* active_window );
private:
    WINDOW* m_active_window;
    int m_cursor_x_pos;
    int m_cursor_y_pos;
};
}

#endif // INPUT_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//
