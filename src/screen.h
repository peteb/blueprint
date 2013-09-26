// screen.h
//
// Description: NCurses screen handling class, handles all things
// related to screens, such as windows and panels as well.
//
//////////////////////////////////////////////////////////////////////

#ifndef SCREEN_H
#define SCREEN_H 1

#include <map>
#include <string>

namespace blueprint
{
    typedef struct PanelInfo {
        PANEL* panel;
        bool hidden;
        WindowInfo window;
    } PANELINFO;

    typedef struct WindowInfo {
        int startx;
        int starty;
        int height;
        int width;
        WIN_BORDER border;
    } WIN;
    
    class Screen
    {
    public:
        Screen();
        ~Screen();
        void create_panel(int x, int y, int width, int height, bool hidden);
    private:
        /** 
         * Initializes the screen
         */
        void init();

        /** 
         * Releases any resources allocated
         */
        void cleanup();

        /*
         * Map holds any number of panels with names
         */
        std::map<std::string, PANEL*> m_panels;
    };
}

#endif // SCREEN_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//
