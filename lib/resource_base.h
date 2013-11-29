#ifndef _RESOURCE_BASE_H_
#define _RESOURCE_BASE_H_

// Resource handler class, taking care of textures, images, and audio.

// own
#include "common.h"

// std
#include <string>
#include <map>

// SFML
#include <SFML/Graphics.hpp>

namespace res
{
    class ResourceBase
    {
    public:
        ResourceBase();
        ~ResourceBase();
        
        void load( uint32 ID, const std::string& filename );
        const sf::Texture& get( uint32 id );

    private:
        std::map< uint32, std::unique_ptr< sf::Texture >> m_data;
    };

}

#endif // _RESOURCE_BASE_H_
