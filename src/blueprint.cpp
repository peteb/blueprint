// -------------------------------------------------------------------------------------------------
//
// Blueprint
//
// -------------------------------------------------------------------------------------------------

#include "blueprint.h"

#include "world_view.h"
#include "input.h"

#include <ncurses.h>

#include <glog/logging.h>

#include <iostream>


using namespace blueprint;

// Start the screen
// The screen contains two panels one main panel at the top, which is a view of the world.
// One at the bottom a much thinner one that contains information.

int main( int argc, char* argv[] )
{
    // Initialize google logging
    google::InitGoogleLogging( argv[0] );
    FLAGS_logtostderr = 1;
    DLOG( INFO ) << " Starting Blueprint ";

    WorldView wv;
    wv.create_fullterminal_panel();

    Input input;
    
    return 0;
}

