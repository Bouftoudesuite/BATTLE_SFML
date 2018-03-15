#ifndef _CSCREEN_HH_
# define _CSCREEN_HH_

#define CLOSE -1
#define MENU 0
#define PLAY 1
#define END 2
#define MAX_PLAYER 7

class Cscreen
{
public:
    virtual int Run (sf::RenderWindow &window) = 0;
};

#endif
