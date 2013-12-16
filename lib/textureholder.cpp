#include "textureholder.h"

// SFML
#include <SFML/Graphics.hpp>

// GLog
#include <glog/logging.h>

// std
#include <memory>
#include <map>
#include <stdexcept>

using namespace VW;

TextureHolder::TextureHolder( )
{
}

void TextureHolder::load( Textures::ID id, const std::string& filename )
{
    std::unique_ptr< sf::Texture > texture( new sf::Texture( ) );
    if ( !texture->loadFromFile( filename ) ) {
        throw std::runtime_error("TextureHolder::load - Failed to load "
                                 + filename);
    }

    auto res = m_textures.insert(
                std::make_pair( id, std::move( texture ) ) ).second;
    if (! res ) {
        LOG(WARNING) << "TextureHolder::load texture already loaded";
    }
}

sf::Texture& TextureHolder::get( Textures::ID id )
{
    auto found = m_textures.find( id );
    return *found->second;
}

const sf::Texture& TextureHolder::get( Textures::ID id ) const
{
    const auto found = m_textures.find( id );
    return *found->second;
}
