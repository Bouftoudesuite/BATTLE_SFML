#ifndef _CHAT_HH_
# define _CHAT_HH_

#include <SFML/Graphics.hpp>
#include "Map.hh"

class Chat : public sf::Drawable, sf::Transformable
{
public:
	bool load(const std::string& tileset, sf::Vector2u tileSize, Map const& _map);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Texture _tileset;
	sf::Vector2u _tileSize;
	sf::VertexArray _vertices;
};

#endif
