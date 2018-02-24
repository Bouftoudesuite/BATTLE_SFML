#ifndef _MAP_HH_
# define _MAP_HH_

#include "CellType.hh"
#include "CellProperty.hh"
#include "Unit.hh"

class Map : public sf::Drawable, public sf::Transformable
{
public:
    Map();
    ~Map();
    unsigned int getWidth() const;
    unsigned int getHeight() const;
    CellType getCell(unsigned int x, unsigned int y) const;
    CellProperty getCellProperties(unsigned int x, unsigned int y);
    bool canGo(unsigned int x, unsigned int y, Unit const&);
    static unsigned int getDistanceBetween(unsigned int firstX, unsigned int firstY, unsigned int secondX, unsigned int secondY);
    bool load(const std::string& tileset, sf::Vector2u tileSize, unsigned int width, unsigned int height);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    unsigned int _width;
    unsigned int _height;
    CellType **_cells;
    sf::VertexArray _vertices;
    sf::Texture _tileset;
};

CellType** parseMap(unsigned int* width, unsigned int* height);

#endif
