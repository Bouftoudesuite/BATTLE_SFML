#ifndef _MENU_HH_
# define _MENU_HH_

#include <SFML/Graphics.hpp> 
#include <SFML/Audio.hpp>
#include "Cscreen.hh"

#define PLAY 1
#define CLOSE 2
#define MAX_PLAYER 7

class Menu : public Cscreen
{
public:
    Menu(unsigned int width, unsigned int height);
    ~Menu();
    int getSelectedItem() const;
    void draw(sf::RenderWindow &window);
    void MoveUp();
    void MoveDown();
    int Run (sf::RenderWindow &window) override;
private:
    int _selectedItemIndex;
    sf::Font _font;
    sf::Text _title;
    sf::Text _menu[MAX_PLAYER];
};

#endif
