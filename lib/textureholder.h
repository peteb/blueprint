#ifndef TEXTUREHOLDER_H
#define TEXTUREHOLDER_H

// SFML
#include <SFML/Graphics.hpp>

// std
#include <string>
#include <memory>

namespace VW
{

namespace Textures
{
enum ID { Landscape };
}

class TextureHolder
{
public:
    TextureHolder();
    void load( Textures::ID id, const std::string& filename );
    sf::Texture& get(Textures::ID id);
    const sf::Texture& get(Textures::ID id) const;
private:
    typedef std::map< Textures::ID, std::unique_ptr< sf::Texture > > TextureMap;
    TextureMap m_textures;
};

} // namespace VW

#endif // TEXTUREHOLDER_H
