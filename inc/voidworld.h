#ifndef _VOIDWORLD_H_
#define _VOIDWORLD_H_

// std
#include <cstdint>
#include <memory>
#include <string>

// SFML
#include <SFML/Graphics.hpp>

//--------------------------------------------------------------------
namespace VW
{

class VoidWorld
    {
    public:
        VoidWorld();
        ~VoidWorld();
        void set_data_source(const char* data, int x, int y);
        void update_entity_position( int x, int y);

        // Resource handling methods
        void load_resource( u_int32_t id, const std::string& name );

        template < typename ResourceId, typename ResourceType >
        const ResourceType& get_resource( ResourceId id ) const;

    private:
        class Impl;
        std::shared_ptr<Impl> m_pImpl;
    };

} // namespace VW

#endif /* _VOIDWORLD_H_ */
