#include "Star.hh"

void Star::setX(unsigned int x)
{
    _x = x;
}

void Star::setY(unsigned int y)
{
    _y = y;
}

bool Star::load(const std::string& tileset, sf::Vector2u tileSize)
{
    if (!_tileset.loadFromFile(tileset))
    {
        return (false);
    }

    _tileSize = tileSize;
    _vertices.setPrimitiveType(sf::Quads);
    _vertices.resize(4);

    _quad = &_vertices[0];

    _quad[0].position = sf::Vector2f(_x * _tileSize.x, _y * _tileSize.y);
    _quad[1].position = sf::Vector2f((_x + 1) * _tileSize.x, _y * _tileSize.y);
    _quad[2].position = sf::Vector2f((_x + 1) * _tileSize.x, (_y + 1) * _tileSize.y);
    _quad[3].position = sf::Vector2f(_x * _tileSize.x, (_y + 1) * _tileSize.y);

    _quad[0].texCoords = sf::Vector2f(0 * _tileSize.x, 0 * _tileSize.y);
    _quad[1].texCoords = sf::Vector2f((0 + 1) * _tileSize.x, 0 * _tileSize.y);
    _quad[2].texCoords = sf::Vector2f((0 + 1) * _tileSize.x, (0 + 1) * _tileSize.y);
    _quad[3].texCoords = sf::Vector2f(0 * _tileSize.x, (0 + 1) * _tileSize.y);

    return (true);
}

void Star::reload()
{
    _quad[0].position = sf::Vector2f(_x * _tileSize.x, _y * _tileSize.y);
    _quad[1].position = sf::Vector2f((_x + 1) * _tileSize.x, _y * _tileSize.y);
    _quad[2].position = sf::Vector2f((_x + 1) * _tileSize.x, (_y + 1) * _tileSize.y);
    _quad[3].position = sf::Vector2f(_x * _tileSize.x, (_y + 1) * _tileSize.y);
}

void Star::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &_tileset;
    target.draw(_vertices, states);
}