#include "Unit.hh"

Unit::Unit(unsigned int x, unsigned int y, Player& player) : _x(x), _y(y), _player(player)
{}

bool Unit::isDead() const
{
    return (getHp() <= 0);
}

unsigned int Unit::getX() const
{
    return (_x);
}

unsigned int Unit::getY() const
{
    return (_y);
}

unsigned int Unit::getHp() const
{
    return (_stats._hp);
}

unsigned int Unit::getPp() const
{
    return (_stats._pp);
}

unsigned int Unit::getAp() const
{
    return (_stats._ap);
}

unsigned int Unit::getMp() const
{
    return (_stats._mp);
}

unsigned int Unit::getHpMax() const
{
    return (_stats._hpMax);
}

unsigned int Unit::getPpMax() const
{
    return (_stats._ppMax);
}

unsigned int Unit::getApMax() const
{
    return (_stats._apMax);
}

unsigned int Unit::getMpMax() const
{
    return (_stats._mpMax);
}

Player& Unit::getOwner()
{
    return (_player);
}

void Unit::setX(unsigned int x)
{
    _x = x;
}

void Unit::setY(unsigned int y)
{
    _y = y;
}

void Unit::setHp(unsigned int hp)
{
    _stats._hp = hp;
}

void Unit::setPp(unsigned int pp)
{
    _stats._pp = pp;
}

void Unit::setAp(unsigned int ap)
{
    _stats._ap = ap;
}

void Unit::setMp(unsigned int mp)
{
    _stats._mp = mp;
}

void Unit::setHpMax(unsigned int hp)
{
    _stats._hpMax = hp;
}

void Unit::setPpMax(unsigned int pp)
{
    _stats._ppMax = pp;
}

void Unit::setApMax(unsigned int ap)
{
    _stats._apMax = ap;
}

void Unit::setMpMax(unsigned int mp)
{
    _stats._mpMax = mp;
}

void Unit::setOwner(Player &player)
{
    _player = player;
}

void Unit::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &_tileset;
    target.draw(_vertices, states);
}