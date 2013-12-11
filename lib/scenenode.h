#ifndef _SCENENODE_H_
#define _SCENENODE_H_

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

class SceneNode :
        public sf::Drawable,
        public sf::Transformable,
        private sf::NonCopyable
{
public:
    typedef std::unique_ptr< SceneNode > Ptr;
    SceneNode( );

    void attach_child( Ptr child );
    Ptr detach_child( const SceneNode& node );

// -------------------------------------------------------------------------------------------------

private:
    virtual void draw( sf::RenderTarget& target,sf::RenderStates states ) const;
    virtual void draw_current( sf::RenderTarget& target,
                              sf::RenderStates states ) const;    
    void draw_children( sf::RenderTarget& target, sf::RenderStates states ) const;

private:
    std::vector< Ptr > m_children;
    SceneNode* m_parent;
};

#endif // _SCENENODE_H_
