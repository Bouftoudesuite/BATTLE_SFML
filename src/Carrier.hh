#ifndef _CARRIER_HH_
# define _CARRIER_HH_

#include <SFML/Graphics.hpp> 
#include <SFML/Audio.hpp>
#include "UnitField.hh"
#include "Unit.hh"
#include "Stats.hh"

class Carrier : public Unit
{
public:
    UnitField getField() const override;
    unsigned int getCost() const override;
    unsigned int getAttackRange() const override;
    unsigned int getAttackMinRange() const override;
    unsigned int getAttackArea() const override;
    static Stats const& getBaseStats();
    void resetStats() override;
    void resetActions() override;
};

#endif
