#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <cstdint>
#include <SFML/Graphics.hpp>

namespace vw
{

class Entity : public sf::Drawable, public sf::Transformable
{
public:
    Entity();
    virtual ~Entity();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        states.texture = &m_texture;
        target.draw( m_vertices, states );
    }

    sf::VertexArray m_vertices;
    sf::Texture m_texture;
};

}

#endif /* _ENTITY_H_ */
