#include "void.h"

using namespace world;

static std::string testmap = { // x:52, y:17
    "#####################################################"
    "#                                                   #"
    "#                                                   #"
    "#       ####    #               #                   #"
    "#               #               #                   #"
    "#       #      ##               #                   #"
    "#       #           ###    ######                   #"
    "#  ######                                 #         #"
    "#                                         #         #"
    "#                        @                #         #"
    "#                                                   #"
    "#                                                   #"
    "#                                                   #"
    "#                ## # # ##### #    #####            #"
    "#                                      #            #"
    "#                                      #            #"
    "#                                      #            #"
    "#####################################################"
};


Void::Void()
{
    m_omni.set_data_source( testmap.c_str(), 52, 17 );
    m_omni.update_entity_position( 25, 9 );
}

Void::~Void()
{

}
