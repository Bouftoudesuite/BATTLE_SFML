#ifndef _UNIT_HH_
# define _UNIT_HH_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "UnitField.hh"
#include "Player.hh"
#include "Stats.hh"
#include "Direction.hh"

class Unit : public sf::Drawable, public sf::Transformable
{
public:
    Unit(unsigned int x, unsigned int y, Player &player);
    bool isDead() const;
    unsigned int getX() const;
    unsigned int getY() const;
    unsigned int getHp() const;
    unsigned int getPp() const;
    unsigned int getAp() const;
    unsigned int getMp() const;
    unsigned int getHpMax() const;
    unsigned int getPpMax() const;
    unsigned int getApMax() const;
    unsigned int getMpMax() const;
    Player& getOwner();
    sf::Vector2u getTilesize() const;
    virtual UnitField getField() const = 0;
    virtual unsigned int getCost() const = 0;
    virtual unsigned int getAttackRange() const = 0;
    virtual unsigned int getAttackMinRange() const = 0;
    virtual unsigned int getAttackArea() const = 0;
    virtual unsigned int getAttackDammage() const = 0;
    void setX(unsigned int x);
    void setY(unsigned int y);
    void setHp(unsigned int hp);
    void setPp(unsigned int pp);
    void setAp(unsigned int ap);
    void setMp(unsigned int mp);
    void setHpMax(unsigned int hp);
    void setPpMax(unsigned int pp);
    void setApMax(unsigned int ap);
    void setMpMax(unsigned int mp);
    void setOwner(Player& player);
    void printInfo();
    virtual void resetStats() = 0;
    virtual void resetActions() = 0;
    virtual void turn(Direction direction) = 0;
    virtual bool load(const std::string& tileset, sf::Vector2u tileSize) = 0;
    virtual bool reload() = 0;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
protected:
    sf::Vertex *_quad;
    sf::VertexArray _vertices;
    sf::Texture _tileset;
    sf::Vector2u _tileSize;
    unsigned int _tileNumber;
private:
    unsigned int _x;
    unsigned int _y;
    Player& _player;
    Stats _stats;
};

#endif
