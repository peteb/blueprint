#ifndef _RESOURCE_BASE_H_
#define _RESOURCE_BASE_H_

// Resource handler class, taking care of textures, images, and audio

// std
#include <string>
#include <map>
#include <memory>
#include <cstdint>

// SFML
#include <SFML/Graphics.hpp>

namespace vw
{
    // Exceptions are to be caught in the class holding this class.
    // TODO: Convert into template class

template < typename ResourceId,
           typename ResourceType >
class Resources
{
public:
    typedef std::map< ResourceId, std::unique_ptr< ResourceType > > ResourceData;


    /**
         * @brief Loads a resource assigning it an id
         * @param id to assign to it
         * @param filename to load
         */
    void load( ResourceId id, const std::string& filename );

    /**
         * @brief Gets a texture from the storage
         * @param id of texture to get
         * @return a sf::Texture reference
         */

    const ResourceType& get( ResourceId id );

private:
    ResourceData m_data;
    };

// -------------------------------------------------------------------------------------------------

template < typename ResourceId, typename ResourceType >
void Resources< ResourceId, ResourceType >::load( ResourceId id, const std::string& filename )
{
    std::unique_ptr< ResourceType > res( new ResourceType( ) );
    res->loadFromFile( filename );
    m_data.insert( std::make_pair( id, std::move( res ) ) );
}

template < typename ResourceId, typename ResourceType >
const ResourceType& Resources< ResourceId, ResourceType >::get( ResourceId id )
{
    typename ResourceData::const_iterator pos = m_data.find( id );
    if ( pos != m_data.end() ) {
        return *pos->second.get();
    }
    throw std::runtime_error("Resources::get failed to load resource id: " + id);
}

}

#endif // _RESOURCE_BASE_H_
