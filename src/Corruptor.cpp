#include "Corruptor.hh"

UnitField Corruptor::getField() const
{
    return (Sky);
}

unsigned int Corruptor::getCost() const
{
    return (200);
}

unsigned int Corruptor::getAttackRange() const
{
    return (2);
}

unsigned int Corruptor::getAttackMinRange() const
{
    return (1);
}

unsigned int Corruptor::getAttackArea() const
{
    return (2);
}

Stats const& Corruptor::getBaseStats()
{
    static Stats stats {150, 15, 6, 3, 150, 15, 6, 3};
    return (stats);
}

void Corruptor::resetStats()
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

void Corruptor::resetActions()
{
    static Stats stats {0, 0, 0, 0, 0, 0, 0};

    stats = getBaseStats();
    setAp(stats._ap);
    setMp(stats._mp);
}