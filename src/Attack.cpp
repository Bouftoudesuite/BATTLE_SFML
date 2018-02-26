#include <iostream>
#include "Attack.hh"

Attack::Attack(Game const& game, Unit& unit) : _game(game), _unit(unit)
{}

void Attack::perform(unsigned int x, unsigned int y)
{
    unsigned int i;
    std::vector<Unit*> toAttack;

    i = 0;
    if (_unit.isDead())
    {
        std::cout << "dead units can't attack" << std::endl;
    }
    else if (_unit.getAp() <= 0)
    {
        std::cout << "no more actions can be performed" << std::endl;
    }
    else if (Map::getDistanceBetween(_unit.getX(), _unit.getY(), x, y) > _unit.getAttackArea())
    {
        std::cout << "out of range" << std::endl;
    }
    else
    {
        _unit.setAp(_unit.getAp() - 1);
        toAttack = _game.getInRange(x, y, _unit.getAttackMinRange(), _unit.getAttackRange(), _unit.getField());
        while (i < toAttack.size())
        {
            toAttack[i]->setHp((_unit.getHp() - _unit.getAttackDammage()));
            i++;
        }
    }
}