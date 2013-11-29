#ifndef _VOIDWORLD_H_
#define _VOIDWORLD_H_

// std
#include <cstdint>
#include <memory>
#include <string>

// SFML
#include <SFML/Graphics.hpp>

//--------------------------------------------------------------------
namespace vw
{
    
    namespace Textures
    {
        enum class ID : std::uint32_t
        {
            TERRA_WORLD_TILES = 0,
            VOID_WORLD_TILES
        };
    }
    
//--------------------------------------------------------------------

class VoidWorld
    {
    public:
        VoidWorld();
        ~VoidWorld();
        void set_data_source(const char* data, int x, int y);
        void update_entity_position( int x, int y);

// Resource handling methods

        void load_resource( Textures::ID id, const std::string& name );
        const sf::Texture& get_resource( Textures::ID id );

    private:
        class Impl;
        std::shared_ptr<Impl> m_pImpl;
    };

} // Namespace world

#endif /* _VOIDWORLD_H_ */
