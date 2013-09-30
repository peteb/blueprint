#ifndef _ENTITY_H_
#define _ENTITY_H_

namespace world
{

class Entity
{
public:
    Entity();
    virtual ~Entity();

    // Basic attributes of an entity
    // Using the Metric system
    int weight; // in kg
    int height; // in centimeters
    
    
};

}

#endif /* _ENTITY_H_ */
