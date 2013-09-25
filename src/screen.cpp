// screen.cpp
//
// 
// Description:
//
//////////////////////////////////////////////////////////////////////

#include "screen.h"
#include <ncurses.h>

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
    raw();
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
