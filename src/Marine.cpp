#include "Marine.hh"

UnitField Marine::getField() const
{
    return (Ground);
}

unsigned int Marine::getCost() const
{
    return (50);
}

unsigned int Marine::getAttackRange() const
{
    return (1);
}

unsigned int Marine::getAttackMinRange() const
{
    return (1);
}

unsigned int Marine::getAttackArea() const
{
    return (1);
}

Stats const& Marine::getBaseStats()
{
    static Stats stats {50, 5, 6, 3, 50, 5, 6, 3};
    return (stats);
}

void Marine::resetStats()
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

void Marine::resetActions()
{
    static Stats stats {0, 0, 0, 0, 0, 0, 0, 0};

    stats = getBaseStats();
    setAp(stats._ap);
    setMp(stats._mp);
}