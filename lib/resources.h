#ifndef _RESOURCE_BASE_H_
#define _RESOURCE_BASE_H_

// Resource handler class, taking care of textures, images, and audio.

// own
#include "common.h"

// std
#include <string>
#include <map>
#include <memory>

// SFML
#include <SFML/Graphics.hpp>

namespace vw
{
    // TODO: Convert into template class
    class Resources
    {
    public:     
        typedef std::map< uint32, std::unique_ptr< sf::Texture > > ResourceData;

        /** 
         * @brief Loads a texture assigning it an id
         * 
         * @param ID to assign to it
         * @param filename to load
         */
        void load( uint32 ID, const std::string& filename );

        /** 
         * @brief Gets a texture from storage.
         * 
         * @param id to get
         * 
         * @return bool true if the texture was found
         */
        bool get( uint32 id, sf::Texture& texture )
        {
            ResourceData::const_iterator pos = m_data.find( id );
            if ( pos != m_data.end() ) {
                texture = *pos->second.get();
                return true;
            }
            return false;
        }

    private:
        ResourceData m_data;
    };

}

#endif // _RESOURCE_BASE_H_
