#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <vector>
#include "Game.hh"
#include "Menu.hh"

int main()
{
    int nbScreen;
    std::vector<Cscreen*> screens;
    std::srand(std::time(nullptr));
    sf::RenderWindow window(sf::VideoMode(638, 799), "Final_Game");
	window.setMouseCursorVisible(false);
    Menu menu(window.getSize().x, window.getSize().y);
    Game game(window.getSize().x, window.getSize().y, menu);
	
    nbScreen = 0;
    screens.push_back(&menu);
    screens.push_back(&game);

    while (nbScreen != CLOSE)
    {
        nbScreen = screens[nbScreen]->Run(window);
    }

    window.close();
    return (0);
}
