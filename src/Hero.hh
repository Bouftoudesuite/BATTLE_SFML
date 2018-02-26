#ifndef _HERO_HH_
# define _HERO_HH_

#include <SFML/Graphics.hpp> 
#include <SFML/Audio.hpp>
#include "Unit.hh"

class Hero : public Unit
{
public:
    using Unit::Unit;
    UnitField getField() const override;
	unsigned int getCost() const override;
	unsigned int getAttackRange() const override;
	unsigned int getAttackMinRange() const override;
	unsigned int getAttackArea() const override;
	unsigned int getAttackDammage() const override;
	static Stats const& getBaseStats();
    void resetStats() override;
    void resetActions() override;
    void turn(Direction direction) override;
    bool load(const std::string& tileset, sf::Vector2u tileSize, int width, int height) override;
    bool reload(const std::string& tileset, int width, int height) override;
};


#endif //GAME_HERO_HH
