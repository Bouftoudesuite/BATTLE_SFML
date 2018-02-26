#ifndef _ATTACK_HH_
# define _ATTACK_HH_

#include "Game.hh"
#include "Unit.hh"
#include "Tank.hh"

class Attack
{
public:
    Attack(Game const& game, Unit& unit);
    void perform(unsigned x, unsigned int y);
private:
    Game _game;
    Unit& _unit;
};

#endif
