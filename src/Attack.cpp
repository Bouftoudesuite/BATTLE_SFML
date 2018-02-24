#include <iostream>
#include "Attack.hh"

template<class T>
Attack<T>::Attack(Game const& game, T& unit) : _game(game), _unit(unit)
{}

template<class T>
void Attack<T>::perform(unsigned int x, unsigned int y)
{
    unsigned int i;
    int pourcent;
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
    else if (Map::getDistanceBetween(_unit.getX(), _unit.getY(), x, y) > _unit.getAttackRange()
             || Map::getDistanceBetween(_unit.getX(), _unit.getY(), x, y) < _unit.getAttackMinRange())
    {
        std::cout << "out of range" << std::endl;
    }
    else
    {
        _unit.setAp(_unit.getAp() - 1);
        toAttack = _game.getInRange(x, y, _unit.getAttackMinRange(), _unit.getAttackRange(), _unit.getField());
        while (i < toAttack.size())
        {
            pourcent = 20;
            toAttack[i]->setHp(_unit.getHpMax() * (1 - pourcent / 100));
            i++;
        }
    }
}

Attack<Tank>::Attack(Game const& game, Tank& unit) : _game(game), _unit(unit)
{}

void Attack<Tank>::perform(unsigned int x, unsigned int y)
{
    unsigned int i;
    int pourcent;
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
    else if (Map::getDistanceBetween(_unit.getX(), _unit.getY(), x, y) > _unit.getAttackRange()
             || Map::getDistanceBetween(_unit.getX(), _unit.getY(), x, y) < _unit.getAttackMinRange())
    {
        std::cout << "out of range" << std::endl;
    }
    else
    {
        _unit.setAp(_unit.getAp() - 1);
        toAttack = _game.getInRange(x, y, _unit.getAttackMinRange(), _unit.getAttackRange(), _unit.getField());
        while (i < toAttack.size())
        {
            pourcent = 20;
            if (Map::getDistanceBetween(x, y, toAttack[i]->getX(), toAttack[i]->getY()) < 2)
            {
                pourcent += 20;
            }
            toAttack[i]->setHp(_unit.getHpMax() * (1 - pourcent / 100));
            i++;
        }
    }
}