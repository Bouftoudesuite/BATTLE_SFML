#include <iostream>
#include "Castle.hh"

bool operator==(Castle const& a, Castle const& b)
{
    return (a.getName() == b.getName() && a.getNbTowers() == b.getNbTowers());
}

bool operator!=(Castle const& a, Castle const& b)
{
    return (a.getName() != b.getName() || a.getNbTowers() != b.getNbTowers());
}

bool operator>(Castle const& a, Castle const& b)
{
    return (a.getNbTowers() > b.getNbTowers());
}

bool operator<(Castle const& a, Castle const& b)
{
    return (a.getNbTowers() < b.getNbTowers());
}

bool operator>=(Castle const& a, Castle const& b)
{
    return (a.getNbTowers() >= b.getNbTowers());
}

bool operator<=(Castle const& a, Castle const& b)
{
    return (a.getNbTowers() <= b.getNbTowers());
}

Castle::Castle(std::string const& name) : _nbTowers(0), _name(name)
{}

int Castle::getNbTowers() const
{
    return (_nbTowers);
}

const std::string& Castle::getName() const
{
    return (_name);
}

void Castle::SetNbTowers(const int nbTowers)
{
    _nbTowers = nbTowers;
}

void Castle::CloseGates()
{
    std::cout << "Close the gates!" << std::endl;
}

void Castle::CloseGates(int nbDoors)
{
    std::cout << "Close only " << nbDoors << " doors" << std::endl;
}