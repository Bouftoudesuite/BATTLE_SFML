#include <iostream>
#include "Attack.hh"

Attack::Attack(Game& game, Unit& unit) : _game(game), _unit(unit)
{}

void Attack::perform(unsigned int x, unsigned int y)
{
    unsigned int i;
    std::vector<Unit*> toAttack;

    i = 0;
    if (_unit.isDead())
    {
        _game.getChat().addMessage("dead units can't attack", sf::Color::Red);
    }
    else if (_unit.getAp() <= 0)
    {
        _game.getChat().addMessage("no more actions can be performed", sf::Color::Red);
    }
    else if (Map::getDistanceBetween(_unit.getX(), _unit.getY(), x, y) > _unit.getAttackArea())
    {
        _game.getChat().addMessage("Attack: out of range", sf::Color::Red);
    }
    else
    {
        _unit.setAp(_unit.getAp() - 1);
        toAttack = _game.getInRange(x, y, _unit.getAttackMinRange(), _unit.getAttackRange(), _unit.getField());
        while (i < toAttack.size())
        {
			if ((int)toAttack[i]->getHp() - (int)_unit.getAttackDammage() >= 0)
			{
				toAttack[i]->setHp(toAttack[i]->getHp() - _unit.getAttackDammage());
			}
			else
			{
				toAttack[i]->setHp(0);
			}
            _game.getChat().addMessage(_unit.getOwner().getName() + " lance une attaque", sf::Color::Cyan);
            _game.getChat().addMessage(_unit.getOwner().getName() + " inflige -" + std::to_string(_unit.getAttackDammage()) + "pv au " + toAttack[i]->getOwner().getName(), sf::Color::Cyan);
            i++;
        }
    }
}