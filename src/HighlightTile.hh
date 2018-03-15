#ifndef _HIGHLIGHTTILE_HH_
#define _HIGHLIGHTTILE_HH_

#include <SFML/Graphics.hpp>

class HighlightTile : public sf::Drawable, public sf::Transformable
{
public:
    unsigned int getTileNumber() const;
    void setX(unsigned int x);
    void setY(unsigned int y);
    void setTileNumber(unsigned int tileNumber);
    bool load(const std::string& tileset, sf::Vector2u tileSize);
    void reload();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    unsigned int _x;
    unsigned int _y;
    sf::Vertex *_quad;
    sf::VertexArray _vertices;
    sf::Texture _tileset;
    sf::Vector2u _tileSize;
    unsigned int _tileNumber;
};


#endif /* _HIGHLIGHTTILE_HH_ */
