#ifndef _PREVIEWATTACKZONE_HH_
# define _PREVIEWATTACKZONE_HH_

#include <SFML/Graphics.hpp>
#include "Unit.hh"

class PreviewAttackZone : public sf::Drawable, public sf::Transformable
{
public:
    bool load(Unit const& unit, const std::string& tileset, sf::Vector2u tileSize, std::vector<sf::Vector2u> posColateral);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    sf::Texture _tileset;
    sf::Vector2u _tileSize;
    sf::VertexArray _vertices;
};

#endif
