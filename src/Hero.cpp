#include "Hero.hh"
#include <iostream>

UnitField Hero::getField() const
{
    return (Ground);
}

unsigned int Hero::getCost() const
{
    return (8000);
}

unsigned int Hero::getAttackRange() const
{
    return (1);
}

unsigned int Hero::getAttackMinRange() const
{
    return (1);
}

unsigned int Hero::getAttackArea() const
{
    return (1);
}

Stats const& Hero::getBaseStats()
{
    static Stats stats {2000, 30, 6, 3, 2000, 30, 6, 3};
    return (stats);
}

void Hero::resetStats()
{
    static Stats stats {0, 0, 0, 0, 0, 0, 0, 0};

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

void Hero::resetActions()
{
    static Stats stats {0, 0, 0, 0, 0, 0, 0, 0};

    stats = getBaseStats();
    setAp(stats._ap);
    setMp(stats._mp);
}

void Hero::turn(Direction direction)
{
    if (getOwner().getId() == 1)
    {
        switch (direction)
        {
            case North:
                _tileNumber = 37;
                break;

            case South:
                _tileNumber = 1;
                break;

            case East:
                _tileNumber = 13;
                break;

            case West:
                _tileNumber = 25;
                break;
        }
    }

    else if (getOwner().getId() == 2)
    {
        switch (direction)
        {
            case North:
                _tileNumber = 40;
                break;

            case South:
                _tileNumber = 4;
                break;

            case East:
                _tileNumber = 16;
                break;

            case West:
                _tileNumber = 28;
                break;
        }
    }

    else if (getOwner().getId() == 3)
    {
        switch (direction)
        {
            case North:
                _tileNumber = 43;
                break;

            case South:
                _tileNumber = 7;
                break;

            case East:
                _tileNumber = 19;
                break;

            case West:
                _tileNumber = 31;
                break;
        }
    }

    else if (getOwner().getId() == 4)
    {
        switch (direction)
        {
            case North:
                _tileNumber = 46;
                break;

            case South:
                _tileNumber = 10;
                break;

            case East:
                _tileNumber = 22;
                break;

            case West:
                _tileNumber = 34;
                break;
        }
    }

    else if (getOwner().getId() == 4)
    {
        switch (direction)
        {
            case North:
                _tileNumber = 46;
                break;

            case South:
                _tileNumber = 10;
                break;

            case East:
                _tileNumber = 22;
                break;

            case West:
                _tileNumber = 34;
                break;
        }
    }

    else if (getOwner().getId() == 5)
    {
        switch (direction)
        {
            case North:
                _tileNumber = 85;
                break;

            case South:
                _tileNumber = 49;
                break;

            case East:
                _tileNumber = 61;
                break;

            case West:
                _tileNumber = 73;
                break;
        }
    }

    else if (getOwner().getId() == 6)
    {
        switch (direction)
        {
            case North:
                _tileNumber = 88;
                break;

            case South:
                _tileNumber = 52;
                break;

            case East:
                _tileNumber = 64;
                break;

            case West:
                _tileNumber = 76;
                break;
        }
    }

    else if (getOwner().getId() == 7)
    {
        switch (direction)
        {
            case North:
                _tileNumber = 91;
                break;

            case South:
                _tileNumber = 55;
                break;

            case East:
                _tileNumber = 67;
                break;

            case West:
                _tileNumber = 79;
                break;
        }
    }

    else if (getOwner().getId() == 8)
    {
        switch (direction)
        {
            case North:
                _tileNumber = 94;
                break;

            case South:
                _tileNumber = 58;
                break;

            case East:
                _tileNumber = 70;
                break;

            case West:
                _tileNumber = 82;
                break;
        }
    }
}


bool Hero::load(const std::string& tileset, sf::Vector2u tileSize, int width, int height)
{
    int i = getX();
    int j = getY();

    if (!_tileset.loadFromFile(tileset))
    {
        return (false);
    }

    _vertices.setPrimitiveType(sf::Quads);
    _vertices.resize(width * height * 4);

    switch (getOwner().getId())
    {
        case 1:
            _tileNumber = 1;
            break;

        case 2:
            _tileNumber = 4;
            break;

        case 3:
            _tileNumber = 7;
            break;

        case 4:
            _tileNumber = 10;
            break;

        case 5:
            _tileNumber = 49;
            break;

        case 6:
            _tileNumber = 52;
            break;

        case 7:
            _tileNumber = 55;
            break;

        case 8:
            _tileNumber = 58;
            break;

        default:
            _tileNumber = 1;
            break;
    }

    unsigned int tu = _tileNumber % (_tileset.getSize().x / tileSize.x);
    unsigned int tv = _tileNumber / (_tileset.getSize().x / tileSize.x);

    _quad = &_vertices[(i + j * width) * 4];

    _quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
    _quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
    _quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
    _quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

    _quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
    _quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
    _quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
    _quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);

    return (true);
}

bool Hero::reload(const std::string& tileset, sf::Vector2u tileSize, int width, int height)
{
    int i = getX();
    int j = getY();

    if (!_tileset.loadFromFile(tileset))
    {
        return (false);
    }

    unsigned int tu = _tileNumber % (_tileset.getSize().x / tileSize.x);
    unsigned int tv = _tileNumber / (_tileset.getSize().x / tileSize.x);

    _quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
    _quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
    _quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
    _quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

    _quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
    _quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
    _quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
    _quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);


    return (true);
}