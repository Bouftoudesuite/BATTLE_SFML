#include "Roach.hh"

UnitField Roach::getField() const
{
    return (Ground);
}

unsigned int Roach::getCost() const
{
    return (150);
}

unsigned int Roach::getAttackRange() const
{
    return (2);
}

unsigned int Roach::getAttackMinRange() const
{
    return (1);
}

unsigned int Roach::getAttackArea() const
{
    return (1);
}

Stats const& Roach::getBaseStats()
{
    static Stats stats {200, 5, 6, 3, 200, 5, 6, 3};
    return (stats);
}

void Roach::resetStats()
{
    Stats stats {0, 0, 0, 0, 0, 0, 0, 0};

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

void Roach::resetActions()
{
    static Stats stats {0, 0, 0, 0, 0, 0, 0, 0};

    stats = getBaseStats();
    setAp(stats._ap);
    setMp(stats._mp);
}