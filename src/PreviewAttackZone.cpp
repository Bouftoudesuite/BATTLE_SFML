#include "PreviewAttackZone.hh"

#include "AttackArea.hh"

bool PreviewAttackZone::load(Unit const& unit, const std::string& tileset, sf::Vector2u tileSize, std::vector<sf::Vector2u> posColateral)
{
    unsigned int i;

    if (!_tileset.loadFromFile(tileset))
    {
        return (false);
    }
    _tileSize = tileSize;
    _vertices.setPrimitiveType(sf::Quads);
    _vertices.resize(posColateral.size() * 4);

    i = 0;
    while (i < posColateral.size())
    {
        sf::Vertex *quad = &_vertices[i * 4];

        quad[0].position = sf::Vector2f(posColateral[i].x * _tileSize.x, posColateral[i].y * _tileSize.y);
        quad[1].position = sf::Vector2f((posColateral[i].x + 1) * _tileSize.x, posColateral[i].y * _tileSize.y);
        quad[2].position = sf::Vector2f((posColateral[i].x + 1) * _tileSize.x, (posColateral[i].y + 1) * _tileSize.y);
        quad[3].position = sf::Vector2f(posColateral[i].x * _tileSize.x, (posColateral[i].y + 1) * _tileSize.y);

        quad[0].texCoords = sf::Vector2f(0, 0);
        quad[1].texCoords = sf::Vector2f(_tileSize.x, 0);
        quad[2].texCoords = sf::Vector2f(_tileSize.x, _tileSize.y);
        quad[3].texCoords = sf::Vector2f(0, _tileSize.y);

        i++;
    }
    return (true);
}

void PreviewAttackZone::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &_tileset;
    target.draw(_vertices, states);
}