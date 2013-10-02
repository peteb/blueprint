#ifndef _VOIDWORLD_H_
#define _VOIDWORLD_H_

#include <memory>
#include <string>

namespace vw
{
    class VoidWorld
    {
    public:
        VoidWorld();
        ~VoidWorld();
        void set_data_source(const char* data, int x, int y);
        void update_entity_position( int x, int y);
    private:
        class Impl;
        std::shared_ptr<Impl> m_pImpl;
    };

} // Namespace world

#endif /* _VOIDWORLD_H_ */
