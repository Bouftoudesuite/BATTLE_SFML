#ifndef _CHAT_HH_
# define _CHAT_HH_

#include <SFML/Graphics.hpp>
#include "Map.hh"

#define MAX_MESSAGE 5

class Chat : public sf::Drawable, sf::Transformable
{
public:
	bool load(const std::string & tileset, sf::Vector2u tileSize, Map const& _map, sf::RenderWindow& window);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void drawMessage(sf::RenderWindow& window);
	void addMessage(std::string newMessage, sf::Color color);
private:
	sf::Font _font;
	sf::Text _message[5];
	sf::Texture _tileset;
	sf::Vector2u _tileSize;
	sf::VertexArray _vertices;
};

#endif
