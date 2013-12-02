#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <cstdint>

namespace vw
{

class Entity
{
public:
    Entity();
    virtual ~Entity();

    // Basic attributes of an entity
    // Using the Metric system
    uint32_t weight; // in kg
    uint32_t height; // in centimeters
    
};

}

#endif /* _ENTITY_H_ */
