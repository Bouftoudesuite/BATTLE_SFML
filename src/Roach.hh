#ifndef _ROACH_HH_
# define _ROACH_HH_

#include "Unit.hh"
#include "Stats.hh"

class Roach : public Unit
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
