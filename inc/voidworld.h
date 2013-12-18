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
private:
        class Impl;
        std::shared_ptr<Impl> m_pImpl;
    };

} // namespace VW

#endif /* _VOIDWORLD_H_ */
