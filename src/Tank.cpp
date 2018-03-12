#include "Tank.hh"

UnitField Tank::getField() const
{
    return (Ground);
}

unsigned int Tank::getCost() const
{
    return (300);
}

unsigned int Tank::getAttackRange() const
{
    return (5);
}

unsigned int Tank::getAttackMinRange() const
{
    return (2);
}

unsigned int Tank::getAttackArea() const
{
    return (4);
}

Stats const& Tank::getBaseStats()
{
    static Stats stats {200, 20, 6, 3, 200, 20, 6, 3};
    return (stats);
}

void Tank::resetStats()
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

void Tank::resetActions()
{
    static Stats stats {0, 0, 0, 0, 0, 0, 0, 0};

    stats = getBaseStats();
    setAp(stats._ap);
    setMp(stats._mp);
}