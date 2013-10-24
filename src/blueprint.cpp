// -------------------------------------------------------------------------------------------------
//
// Blueprint
//
// -------------------------------------------------------------------------------------------------

#include "blueprint.h"

#include "voidworld.h"
#include "world_view.h"
#include "input.h"

#include <ncurses.h>

#include <glog/logging.h>

#include <iostream>

using namespace blueprint;

static std::string testmap = { // x:52, y:17
    "#####################################################"
    "#                                                   #"
    "#                                                   #"
    "#       ####    #    ##         #                   #"
    "#               #     #         #                   #"
    "#       #      ##        ###    #                   #"
    "#       #           #      ######                   #"
    "#  ######             #  #                #         #"
    "#                     #                   #         #"
    "#                       @                 #         #"
    "#                                                   #"
    "#                                                   #"
    "#                                                   #"
    "#                ## # # ##### #    #####            #"
    "#                                      #            #"
    "#                                      #            #"
    "#                                      #            #"
    "#####################################################"
};

// Start the screen
// The screen contains two panels one main panel at the top, which is a view of the world.
// One at the bottom a much thinner one that contains information.

int main( int argc, char* argv[] )
{
    // Initialize google logging
    google::InitGoogleLogging( argv[0] );
    FLAGS_logtostderr = 1;
    DLOG( INFO ) << " Starting Blueprint ";

    // Initializing ncurses

//    initscr( );
//    if ( has_colors() == FALSE ) {
//        LOG(WARNING) << "Your terminal lacks colors.";
//    } else {
//        start_color( );
//    }
//    init_pair( 1, COLOR_RED, COLOR_BLACK );
//    attron( COLOR_PAIR( 1 ) );
    // Setting up the world

    //WorldView wv;
    //wv.create_fullterminal_panel( "Main", true, false );

    //Input input;
    vw::VoidWorld world;
    world.set_data_source( testmap.c_str(), 53, 18 );
    world.update_entity_position( 25, 9 );

    return 0;
}

