#include "Ursadon.hh"

UnitField Ursadon::getField() const
{
    return (Water);
}

unsigned int Ursadon::getCost() const
{
    return (30);
}

unsigned int Ursadon::getAttackRange() const
{
    return (10);
}

unsigned int Ursadon::getAttackMinRange() const
{
    return (1);
}

unsigned int Ursadon::getAttackArea() const
{
    return (2);
}

Stats const& Ursadon::getBaseStats()
{
    static Stats stats {300, 2, 6, 3, 300, 2, 6, 3};
    return (stats);
}

void Ursadon::resetStats()
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

void Ursadon::resetActions()
{
    static Stats stats {0, 0, 0, 0, 0, 0, 0, 0};

    stats = getBaseStats();
    setAp(stats._ap);
    setMp(stats._mp);
}