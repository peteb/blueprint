// screen.cpp
//
// 
// Description:
//
//////////////////////////////////////////////////////////////////////

#include "screen.h"
#include <ncurses.h>
#include <panel.h>

using namespace voids;

Screen::Screen()
{
    init();
} 

Screen::~Screen()
{
}

void Screen::init()
{
    initscr();
    start_color();
    raw();
    // TODO: Instantiate input here
    keypad(stdscr, TRUE);
    noecho();
    getch();
}

void Screen::cleanup()
{
}


//////////////////////////////////////////////////////////////////////
// $Log:$
//
