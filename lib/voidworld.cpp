
// own
#include "voidworld.h"
#include "omniview.h"
#include "resources.h"
#include "worldmap.h"
#include "worldloader.h"

// glog
#include <glog/logging.h>

using namespace VW;

// -------------------------------------------------------------------------------------------------
// Implementation class

class VoidWorld::Impl
{
public:
    Impl()
    {}
    ~Impl() {}
private:
    OmniView m_omni;
};

// -------------------------------------------------------------------------------------------------

VoidWorld::VoidWorld()
    : m_pImpl(std::make_shared<Impl>())
{
}

// -------------------------------------------------------------------------------------------------

VoidWorld::~VoidWorld()
{

}

// -------------------------------------------------------------------------------------------------

