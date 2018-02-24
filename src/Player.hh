#ifndef _PLAYER_HH_
# define _PLAYER_HH_

#include <SFML/Graphics.hpp> 
#include <SFML/Audio.hpp>
#include <string>

class Player
{
public:
    Player(unsigned int id, unsigned int budget);
    ~Player();
	unsigned int getId() const;
	unsigned int getBudget() const;
    const std::string& getName() const;
    void setBudget(unsigned int budget);
private:
	unsigned int _id;
    std::string _name;
	unsigned int _budget;
};

#endif
