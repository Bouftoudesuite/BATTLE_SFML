#ifndef _TANK_HH_
# define _TANK_HH_

#include "Unit.hh"
#include "Stats.hh"

class Tank : public Unit
{
public:
    using Unit::Unit;
    UnitField getField() const override;
    unsigned int getCost() const override;
    unsigned int getAttackRange() const override;
    unsigned int getAttackMinRange() const override;
    unsigned  int getAttackArea() const override;
    static Stats const& getBaseStats();
    void resetStats() override;
    void resetActions() override;
    void turn(Direction direction) override;
    bool load(const std::string& tileset, sf::Vector2u tileSize) override;
    bool reload() override;
};

#endif
