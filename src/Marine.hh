#ifndef _MARINE_HH_
# define _MARINE_HH_

#include "UnitField.hh"
#include "Unit.hh"
#include "Stats.hh"

class Marine : public Unit
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
