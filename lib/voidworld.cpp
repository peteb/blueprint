
// own
#include "voidworld.h"
#include "omniview.h"
#include "resources.h"

// glog
#include <glog/logging.h>

using namespace vw;

// -------------------------------------------------------------------------------------------------
// Implementation class

class VoidWorld::Impl
{
public:
    Impl() {}
    ~Impl() {}

    void set_data_source( const char* data, int x, int y )
    {
        m_omni.set_data_source( data, x, y );
    }
// -------------------------------------------------------------------------------------------------

    void update_entity_position( int x, int y )
    {
        m_omni.update_entity_position( x, y );
    }
    
// -------------------------------------------------------------------------------------------------

    const sf::Texture& get_resource( uint32 id, sf::Texture& texture )
    {
        if ( m_resource.get( id, texture ) ) {
            DLOG( INFO ) << "Loaded texture with id: " << id;
        }
        
    }

// -------------------------------------------------------------------------------------------------

private:
    Resources m_resource;
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

void VoidWorld::set_data_source( const char* data, int x, int y)
{
    m_pImpl->set_data_source( data, x, y );

}

// -------------------------------------------------------------------------------------------------

void VoidWorld::update_entity_position( int x, int y)
{
    m_pImpl->update_entity_position( x, y );
}

// -------------------------------------------------------------------------------------------------


// -------------------------------------------------------------------------------------------------

