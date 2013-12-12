
// own
#include "voidworld.h"
#include "omniview.h"
#include "resources.h"
#include "worldloader.h"
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
        create_sperical_wold();
    }
// -------------------------------------------------------------------------------------------------

    void update_entity_position( int x, int y )
    {
        m_omni.update_entity_position( x, y );
    }


// -------------------------------------------------------------------------------------------------

    void create_sperical_wold()
    {
        WorldLoader w;
        w.create_spherical_world();

    }
    
// -------------------------------------------------------------------------------------------------
    template < typename ResourceId >
    void load_resource( ResourceId id, const std::string& name )
    {
        create_sperical_wold();
        m_resource.load( id, name );
    }
// -------------------------------------------------------------------------------------------------
    template < typename ResourceId, typename ResourceType>
    const ResourceType& get_resource( ResourceId id ) const
    {
        return m_resource.get( id );
    }

// -------------------------------------------------------------------------------------------------

private:
    Resources<u_int32_t, sf::Texture> m_resource;
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

template < typename ResourceId, typename ResourceType >
const ResourceType& VoidWorld::get_resource( ResourceId id ) const
{
    m_pImpl->get_resource( id );
}

void VoidWorld::load_resource( u_int32_t id, const std::string& name )
{
    m_pImpl->load_resource( id, name );
}

// -------------------------------------------------------------------------------------------------

