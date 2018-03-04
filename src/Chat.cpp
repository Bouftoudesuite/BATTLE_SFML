#include "Chat.hh"

bool Chat::load(const std::string& tileset, sf::Vector2u tileSize, Map const& _map)
{
	float x;
	float y;
	sf::Vertex* quad;

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
	quad[1].position = sf::Vector2f((x + 1) * (float)_map.getTilesize().y * (float)_map.getHeight(), y * _tileSize.y);
	quad[2].position = sf::Vector2f((x + 1) * (float)_map.getTilesize().y * (float)_map.getHeight(), (y + 1) * _tileSize.y);
	quad[3].position = sf::Vector2f(x * _tileSize.x, (y + 1) * _tileSize.y);

	quad[0].texCoords = sf::Vector2f(0, 0);
	quad[1].texCoords = sf::Vector2f(_tileSize.x, 0);
	quad[2].texCoords = sf::Vector2f(_tileSize.x, _tileSize.y);
	quad[3].texCoords = sf::Vector2f(0, _tileSize.y);

	return (true);
}


void Chat::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &_tileset;
	target.draw(_vertices, states);
}