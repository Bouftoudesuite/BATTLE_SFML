#ifndef _ATTACK_HH_
# define _ATTACK_HH_

#include "Game.hh"
#include "Unit.hh"
#include "Tank.hh"

template<class T>
class Attack
{
public:
    Attack(Game const& game, T& unit);
    void perform(unsigned int x, unsigned int y);
private:
    Game _game;
    T& _unit;
};

template<>
class Attack<Tank>
{
public:
    Attack(Game const& game, Tank& unit);
    void perform(unsigned int x, unsigned int y);
private:
    Game _game;
    Tank& _unit;
};

#endif
