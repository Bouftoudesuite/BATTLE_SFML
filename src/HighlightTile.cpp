#include "HighlightTile.hh"

void HighlightTile::setX(unsigned int x)
{
    _x = x;
}
void HighlightTile::setY(unsigned int y)
{
    _y = y;
}

void HighlightTile::setTileNumber(unsigned int tileNumber)
{
    _tileNumber = tileNumber;
}

bool HighlightTile::load(const std::string& tileset, sf::Vector2u tileSize)
{
    if (!_tileset.loadFromFile(tileset))
    {
        return (false);
    }
    _tileSize = tileSize;
    _vertices.setPrimitiveType(sf::Quads);
    _vertices.resize(4);


    _quad = &_vertices[0];

/*    _quad[0].position = sf::Vector2f(_x * _tileSize.x, _y * _tileSize.y);
    _quad[1].position = sf::Vector2f((_x + 1) * _tileSize.x, _y * _tileSize.y);
    _quad[2].position = sf::Vector2f((_x + 1) * _tileSize.x, (_y + 1) * _tileSize.y);
    _quad[3].position = sf::Vector2f(_x * _tileSize.x, (_y + 1) * _tileSize.y);

    _quad[0].texCoords = sf::Vector2f(0, 0);
    _quad[1].texCoords = sf::Vector2f(_tileSize.x, _tileSize.y);
    _quad[2].texCoords = sf::Vector2f(_tileSize.x, _tileSize.y);
    _quad[3].texCoords = sf::Vector2f(0, _tileSize.y);
*/
    return (true);
}

void HighlightTile::reload()
{
    unsigned int tu = _tileNumber % (_tileset.getSize().x / _tileSize.x);
    unsigned int tv = _tileNumber / (_tileset.getSize().x / _tileSize.x);

    _quad[0].position = sf::Vector2f(_x * _tileSize.x, _y * _tileSize.y);
    _quad[1].position = sf::Vector2f((_x + 1) * _tileSize.x, _y * _tileSize.y);
    _quad[2].position = sf::Vector2f((_x + 1) * _tileSize.x, (_y + 1) * _tileSize.y);
    _quad[3].position = sf::Vector2f(_x * _tileSize.x, (_y + 1) * _tileSize.y);

    _quad[0].texCoords = sf::Vector2f(tu * _tileSize.x, tv * _tileSize.y);
    _quad[1].texCoords = sf::Vector2f((tu + 1) * _tileSize.x, tv * _tileSize.y);
    _quad[2].texCoords = sf::Vector2f((tu + 1) * _tileSize.x, (tv + 1) * _tileSize.y);
    _quad[3].texCoords = sf::Vector2f(tu * _tileSize.x, (tv + 1) * _tileSize.y);
}

void HighlightTile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &_tileset;
    target.draw(_vertices, states);
}