#include "Chat.hh"

bool Chat::load(const std::string& tileset, sf::Vector2u tileSize, Map const& _map, sf::RenderWindow& window)
{
	float x;
	float y;
	sf::Vertex* quad;


	/* Screen */
	if (!_tileset.loadFromFile(tileset))
	{
		return (false);
	}

	_tileSize = tileSize;
	_vertices.setPrimitiveType(sf::Quads);
	_vertices.resize(4);
	x = 0;
	y = (float)_map.getTilesize().y * (float)_map.getHeight() / (float)_tileSize.y;
	quad = &_vertices[0];

	quad[0].position = sf::Vector2f(x * _tileSize.x, y * _tileSize.y);
	quad[1].position = sf::Vector2f((x + 1) * (float)window.getSize().x, y * _tileSize.y);
	quad[2].position = sf::Vector2f((x + 1) * (float)window.getSize().x, (y + 1) * _tileSize.y);
	quad[3].position = sf::Vector2f(x * _tileSize.x, (y + 1) * _tileSize.y);

	quad[0].texCoords = sf::Vector2f(0, 0);
	quad[1].texCoords = sf::Vector2f(_tileSize.x, 0);
	quad[2].texCoords = sf::Vector2f(_tileSize.x, _tileSize.y);
	quad[3].texCoords = sf::Vector2f(0, _tileSize.y);


	/* Message */
	if (_font.loadFromFile("assets/font/dpcomic.ttf"))
	{
		_message[0].setFont(_font);
		_message[0].setString(" ");
		_message[0].setCharacterSize(15);
		_message[0].setPosition(sf::Vector2f(_map.getTilesize().x * (float)_map.getWidth() / 30, _tileSize.y / (MAX_MESSAGE + 7) * 1 * 1.4 + _map.getTilesize().y * _map.getHeight()));
		_message[1].setFont(_font);
		_message[1].setString(" ");
		_message[1].setCharacterSize(15);
		_message[1].setPosition(sf::Vector2f(_map.getTilesize().x * (float)_map.getWidth() / 30, _tileSize.y / (MAX_MESSAGE + 7) * 2 * 1.4 + _map.getTilesize().y * _map.getHeight()));
		_message[2].setFont(_font);
		_message[2].setString(" ");
		_message[2].setCharacterSize(15);
		_message[2].setPosition(sf::Vector2f(_map.getTilesize().x * (float)_map.getWidth() / 30, _tileSize.y / (MAX_MESSAGE + 7) * 3 * 1.4 + _map.getTilesize().y * _map.getHeight()));
		_message[3].setFont(_font);
		_message[3].setString(" ");
		_message[3].setCharacterSize(15);
		_message[3].setPosition(sf::Vector2f(_map.getTilesize().x * (float)_map.getWidth() / 30, _tileSize.y / (MAX_MESSAGE + 7) * 4 * 1.4 + _map.getTilesize().y * _map.getHeight()));
		_message[4].setFont(_font);
		_message[4].setString(" ");
		_message[4].setCharacterSize(15);
		_message[4].setPosition(sf::Vector2f(_map.getTilesize().x * (float)_map.getWidth() / 30, _tileSize.y / (MAX_MESSAGE + 7) * 5 * 1.4 + _map.getTilesize().y * _map.getHeight()));
	}

	return (true);
}


void Chat::clear()
{
	unsigned int i;

    i = 0;
	while (i < MAX_MESSAGE)
	{
		_message[i].setString(" ");
		i++;
	}
}

void Chat::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &_tileset;
	target.draw(_vertices, states);
}

void Chat::drawMessage(sf::RenderWindow& window)
{
	unsigned int i;

	i = 0;
	while (i < MAX_MESSAGE)
	{
		window.draw(_message[i]);
		i++;
	}
}

void Chat::addMessage(std::string newMessage, sf::Color color)
{
	unsigned int i;
	
	if (_message[4].getString() == " ")
	{
		i = 0;
		while (_message[i].getString() != " " && i < MAX_MESSAGE)
		{
			i++;
		}
		_message[i].setFillColor(color);
		_message[i].setString(newMessage);
	}
	else
	{
		i = 1;
		while (i < MAX_MESSAGE)
		{
			_message[i - 1].setFillColor(_message[i].getFillColor());
			_message[i - 1].setString(_message[i].getString());
			i++;
		}
		_message[i - 1].setFillColor(color);
		_message[i - 1].setString(newMessage);
	}
}