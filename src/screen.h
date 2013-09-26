// screen.h
//
// Description: NCurses screen handling class, handles all things
// related to screens, such as windows and panels as well.
//
//////////////////////////////////////////////////////////////////////

#ifndef SCREEN_H
#define SCREEN_H 1

namespace voids
{
    class Screen
    {
    public:
        Screen();
        ~Screen();
    private:

        /** 
         * Initializes the screen
         */
        void init();

        /** 
         * Releases any resources allocated
         */
        void cleanup();
        
    };
}

#endif // SCREEN_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//
