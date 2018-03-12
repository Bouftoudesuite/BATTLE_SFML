#ifndef _STAR_HH_
#define _STAR_HH_


#include <SFML/Graphics.hpp>

class Star : public sf::Drawable, public sf::Transformable
{
public:
    void setX(unsigned int x);
    void setY(unsigned int y);
    bool load(const std::string& tileset, sf::Vector2u tileSize);
    void reload();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    unsigned _x;
    unsigned _y;
    sf::Vertex *_quad;
    sf::VertexArray _vertices;
    sf::Texture _tileset;
    sf::Vector2u _tileSize;
};


#endif //_STAR_HH_
