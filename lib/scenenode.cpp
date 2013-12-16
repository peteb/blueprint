#include "scenenode.h"

#include <algorithm>
#include <cassert>

using namespace VW;

SceneNode::SceneNode()
{
}

void SceneNode::attach_child( SceneNode::Ptr child )
{
    child->m_parent = this;
    m_children.push_back( std::move( child ) );
}

SceneNode::Ptr SceneNode::detach_child( const SceneNode& node )
{
    auto found = std::find_if( m_children.begin( ), m_children.end( ),
                               [ & ] ( Ptr& p ) -> bool
    { return p.get( ) == &node; } );

     assert( found != m_children.end( ) );
     Ptr result = std::move( *found );
     result->m_parent = nullptr;
     m_children.erase( found );
     return result;
}

void SceneNode::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
	// Apply transform of current node
	states.transform *= getTransform( );

	// Draw node and children with changed transform
	draw_current( target, states );
	draw_children( target, states );
}

void SceneNode::draw_current(sf::RenderTarget&, sf::RenderStates) const
{
	// Do nothing by default
}

void SceneNode::draw_children( sf::RenderTarget& target, sf::RenderStates states ) const
{
    for (const Ptr& child : m_children ) {
        child->draw(target, states);
    }
}
