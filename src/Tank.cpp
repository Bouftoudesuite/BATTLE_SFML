#include "Tank.hh"

UnitField Tank::getField() const
{
    return (Ground);
}

unsigned int Tank::getCost() const
{
    return (300);
}

unsigned int Tank::getAttackRange() const
{
    return (5);
}

unsigned int Tank::getAttackMinRange() const
{
    return (2);
}

unsigned int Tank::getAttackArea() const
{
    return (4);
}

Stats const& Tank::getBaseStats()
{
    static Stats stats {200, 20, 6, 3, 200, 20, 6, 3};
    return (stats);
}

void Tank::resetStats()
{
    Stats stats {0, 0, 0, 0, 0, 0, 0, 0};

    stats = getBaseStats();
    setHp(stats._hp);
    setPp(stats._pp);
    setAp(stats._ap);
    setMp(stats._mp);
    setHpMax(stats._hpMax);
    setPpMax(stats._ppMax);
    setApMax(stats._apMax);
    setMpMax(stats._mpMax);
}

void Tank::resetActions()
{
    static Stats stats {0, 0, 0, 0, 0, 0, 0, 0};

    stats = getBaseStats();
    setAp(stats._ap);
    setMp(stats._mp);
}

void Tank::turn(Direction direction)
{

        switch (direction)
        {
            case North:
                _tileNumber = getOwner().getId() - 1;
                break;

            case South:
                _tileNumber = 8 * 17 + getOwner().getId() - 1;
                break;

            case East:
                _tileNumber = 8 * (9 + getOwner().getId() - 1);
                break;

            case West:
                _tileNumber = 8 * (25 + getOwner().getId() - 1);
                break;
        }
}


bool Tank::load(const std::string& tileset, sf::Vector2u tileSize)
{
    int i = getX();
    int j = getY();

    if (!_tileset.loadFromFile(tileset))
    {
        return (false);
    }

    _tileSize = tileSize;
    _vertices.setPrimitiveType(sf::Quads);
    _vertices.resize(4);

    _tileNumber = 8 * (9 + getOwner().getId() - 1);

    unsigned int tu = _tileNumber % (_tileset.getSize().x / _tileSize.x);
    unsigned int tv = _tileNumber / (_tileset.getSize().x / _tileSize.x);

    _quad = &_vertices[0];

    _quad[0].position = sf::Vector2f(i * _tileSize.x, j * _tileSize.y);
    _quad[1].position = sf::Vector2f((i + 1) * _tileSize.x, j * _tileSize.y);
    _quad[2].position = sf::Vector2f((i + 1) * _tileSize.x, (j + 1) * _tileSize.y);
    _quad[3].position = sf::Vector2f(i * _tileSize.x, (j + 1) * _tileSize.y);

    _quad[0].texCoords = sf::Vector2f(tu * _tileSize.x, tv * _tileSize.y);
    _quad[1].texCoords = sf::Vector2f((tu + 1) * _tileSize.x, tv * _tileSize.y);
    _quad[2].texCoords = sf::Vector2f((tu + 1) * _tileSize.x, (tv + 1) * _tileSize.y);
    _quad[3].texCoords = sf::Vector2f(tu * _tileSize.x, (tv + 1) * _tileSize.y);

    return (true);
}

bool Tank::reload()
{
    int i = getX();
    int j = getY();

    unsigned int tu = _tileNumber % (_tileset.getSize().x / _tileSize.x);
    unsigned int tv = _tileNumber / (_tileset.getSize().x / _tileSize.x);

    _quad[0].position = sf::Vector2f(i * _tileSize.x, j * _tileSize.y);
    _quad[1].position = sf::Vector2f((i + 1) * _tileSize.x, j * _tileSize.y);
    _quad[2].position = sf::Vector2f((i + 1) * _tileSize.x, (j + 1) * _tileSize.y);
    _quad[3].position = sf::Vector2f(i * _tileSize.x, (j + 1) * _tileSize.y);

    _quad[0].texCoords = sf::Vector2f(tu * _tileSize.x, tv * _tileSize.y);
    _quad[1].texCoords = sf::Vector2f((tu + 1) * _tileSize.x, tv * _tileSize.y);
    _quad[2].texCoords = sf::Vector2f((tu + 1) * _tileSize.x, (tv + 1) * _tileSize.y);
    _quad[3].texCoords = sf::Vector2f(tu * _tileSize.x, (tv + 1) * _tileSize.y);


    return (true);
}