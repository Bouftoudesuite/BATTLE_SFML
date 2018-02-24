#include <cmath>
#include <cstddef>
#include <fstream>
#include <iostream>
#include "CellProperty.hh"
#include "Map.hh"

Map::Map() :
    _width(20),
    _height(20),
    _cells(parseMap(&_width, &_height))
{}

Map::~Map()
{}

unsigned int Map::getWidth() const
{
    return (_width);
}

unsigned int Map::getHeight() const
{
	return (_height);
}

CellType Map::getCell(unsigned int x, unsigned int y) const
{
    return (_cells[x][y]);
}

CellProperty Map::getCellProperties(unsigned int x, unsigned int y)
{
    int i;
    CellProperty cell;
    i = CellProperty::getCellFlags(getCell(x, y));
    if (i == FLYABLE)
    {
        cell.setFlyable();
    }
    else if (i == WALKABLE)
    {
        cell.setWalkable();
    }
    else if (i == SWIMMABLE)
    {
        cell.setSwimmable();
    }
    else if (i == (FLYABLE | WALKABLE))
    {
        cell.setFlyable();
        cell.setWalkable();
    }
    else if (i == (SWIMMABLE | FLYABLE))
    {
        cell.setSwimmable();
        cell.setFlyable();
    }
    else if (i == (SWIMMABLE | WALKABLE))
    {
        cell.setSwimmable();
        cell.setWalkable();
    }
    else if (i == (SWIMMABLE | WALKABLE | FLYABLE))
    {
        cell.setSwimmable();
        cell.setWalkable();
        cell.setFlyable();
    }
    return (cell);
}

bool Map::canGo(unsigned int x, unsigned int y, const Unit& unit)
{
    UnitField field;
    CellProperty property;

    property = getCellProperties(x, y);
    field = unit.getField();
    if (field == Sky && property.isFlyable())
    {
        return (true);
    }
    else if (field == Ground && property.isWalkable())
    {
        return (true);
    }
    else if (field == Water && property.isFlyable())
    {
        return (true);
    }
    return (false);
}

CellType** parseMap(unsigned int* width, unsigned int* height)
{
    char tmp;
    unsigned int i;
    unsigned int j;
    unsigned int k;
    CellType** _cells;

    std::ifstream file("map/map.txt", std::ios::in);
    if(file)
    {
        i = 0;
        k = 0;
        _cells = new CellType*[*width];
        while (i < *width)
        {
            _cells[i] = new CellType[*height];
            i++;
        }
        j = 0;
        while (j < *height)
        {
            i = 0;
            while (i < *width)
            {
                file.get(tmp);
                if (tmp == 'G')
                    _cells[i][j] = GrassCell;
                else if (tmp == 'W')
                    _cells[i][j] = WaterCell;
                else if (tmp == 'R')
                    _cells[i][j] = RockCell;
                else if (tmp == 'M')
                    _cells[i][j] = MountainCell;
                else if (tmp == '\n')
                    i--;
                else
                {
                    while (k < i)
                    {
                        delete[] _cells[k];
                        k++;
                    }
                    delete[] _cells;
                    std::cerr << "invalid map data" << std::endl;
                    return (nullptr);
                }
                i++;
            }
            j++;
        }
        file.close();
        return (_cells);
    }
    else
    {
        std::cout << "Cannot open file !" << std::endl;
        return (nullptr);
    }
}

unsigned int Map::getDistanceBetween(unsigned int firstX, unsigned int firstY, unsigned int secondX, unsigned int secondY)
{
    unsigned int distance;

    distance = (unsigned int)std::abs((int)firstX - (int)firstY) + (unsigned int)std::abs((int)secondX - (int)secondY);
    return (distance);
}

bool Map::load(const std::string& tileset, sf::Vector2u tileSize, unsigned int width, unsigned int height)
{
    unsigned int i;
    unsigned int j;

    if (!_tileset.loadFromFile(tileset))
    {
        return (false);
    }

    _vertices.setPrimitiveType(sf::Quads);
    _vertices.resize(width * height * 4);

    i = 0;
    while (i < width)
    {
        j = 0;
        while (j < height)
        {
            int tileNumber = getCell(i, j);

            int tu = tileNumber % (_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (_tileset.getSize().x / tileSize.x);

            sf::Vertex* quad = &_vertices[(i + j * width) * 4];

            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);

            j++;
        }
        i++;
    }
    return true;
}


void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &_tileset;
    target.draw(_vertices, states);
}
