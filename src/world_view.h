// -------------------------------------------------------------------------------------------------
//
// Description: NCurses screen handling class, handles all things
// related to screens, such as windows and panels as well.
//
// -------------------------------------------------------------------------------------------------


#ifndef WORLD_VIEW_H
#define WORLD_VIEW_H

#include <map>
#include <string>

#include <panel.h>

// -------------------------------------------------------------------------------------------------

namespace blueprint
{
    
    typedef struct WindowInfo {
        int startx;
        int starty;
        int height;
        int width;
        bool border;
    } WIN;

    typedef struct PanelInfo {
        PANEL* panel;
        bool hidden;
        WindowInfo window;
    } PANELINFO;
    
    class WorldView
    {
    public:
        WorldView();
        ~WorldView();
        /** 
         * 
         * 
         * @param border Add a border or not
         * @param hidden Start hidden or not
         */
        void create_fullterminal_panel( std::string& panel_name, bool border = false, bool hidden = false);

        /** 
         * 
         * 
         * @param x Start x position
         * @param y Start y position
         * @param width Width of panel
         * @param height Height of panel
         * @param border Add a border or not
         * @param hidden Start hidden or not
         */
        void create_panel(int x, int y, int width, int height, bool border = false, bool hidden = false);
    private:
        PANEL* create_panel( std::string& panel_name, int x, int y );

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

#endif // WORLD_VIEW_H

// -------------------------------------------------------------------------------------------------
