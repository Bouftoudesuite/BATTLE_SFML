#include <ctime>
#include <cstdlib>
#include <iostream>
#include "Player.hh"

Player::Player(unsigned int id, unsigned int budget) : _id(id), _name("Joueur" + std::to_string(id)), _budget(budget)
{}

Player::~Player()
{}

unsigned int Player::getId() const
{
    return (_id);
}

unsigned int Player::getBudget() const
{
    return (_budget);
}

const std::string& Player::getName() const
{
    return (_name);
}

void Player::setBudget(unsigned int budget)
{
    _budget = budget;
}