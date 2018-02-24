#include "Carrier.hh"

UnitField Carrier::getField() const
{
    return (Sky);
}

unsigned int Carrier::getCost() const
{
    return (500);
}

unsigned int Carrier::getAttackRange() const
{
    return (5);
}

unsigned int Carrier::getAttackMinRange() const
{
    return (1);
}

unsigned int Carrier::getAttackArea() const
{
    return (4);
}

Stats const& Carrier::getBaseStats()
{
    static Stats stats {450, 30, 6, 3, 450, 30, 6, 3};
    return (stats);
}

void Carrier::resetStats()
{
    static Stats stats {0, 0, 0, 0, 0, 0, 0, 0};

    stats = getBaseStats();
    setHp(stats._hp);
    setPp(stats._pp);
    setAp(stats._ap);
    setMp(stats._mp);
    setHpMax(stats._hpMax);
    setPpMax(stats._ppMax);
    setApMax(stats._apMax);
    setMpMax(stats._mpMax);
}

void Carrier::resetActions()
{
    static Stats stats {0, 0, 0, 0, 0, 0, 0, 0};

    stats = getBaseStats();
    setAp(stats._ap);
    setMp(stats._mp);
}