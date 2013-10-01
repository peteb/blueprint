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
#include <memory>
#include <ncurses.h>
#include <panel.h>
#include <glog/logging.h>

// -------------------------------------------------------------------------------------------------

namespace blueprint
{
    
    class WindowInfo {
    public:
        WindowInfo() :
            startx( 0 ),
            starty ( 0 ),
            lines( 0 ),
            columns( 0),
            window( nullptr )
            {};
        ~WindowInfo() {
            delwin( window );
            DLOG(INFO) << "Deleting window";
        }
        int startx;
        int starty;
        int lines;
        int columns;
        bool border;
        WINDOW* window;
    };

    class PanelInfo {
    public:
        PanelInfo():
            panel( nullptr )
            {};
        ~PanelInfo() {
            del_panel( panel );
            DLOG(INFO) << "Deleting panel";
            
        }
        bool hidden;
        PANEL* panel;
        WindowInfo window_info;
    };
    
    class WorldView
    {
    public:
        WorldView();
        ~WorldView();
        /** 
         * create_fullterminal_panel
         * 
         * @param border Add a border or not
         * @param hidden Start hidden or not
         */
        void create_fullterminal_panel( const char* panel_name, bool border = true, bool hidden = false);

        /** 
         * create_panel
         * 
         * @param startx Start x position
         * @param starty Start y position
         * @param lines Lines of panel
         * @param columns Columns of panel
         * @param border Add a border or not
         * @param hidden Start hidden or not
         */
        bool create_panel( const char* panel_name, int startx, int starty, int lines, int columns, bool border = false, bool hidden = false);
    private:

        /** 
         * Initializes the screen
         */
        void init();

        /** 
         * Releases any resources allocated
         */
        void cleanup();

        void release_panel()
        {
        }

        typedef std::map< std::string, std::shared_ptr<PanelInfo> > PanelData;
        /*
         * Map holds any number of panels with names
         */
        PanelData m_panels;
    };
}

#endif // WORLD_VIEW_H

// -------------------------------------------------------------------------------------------------
