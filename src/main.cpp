#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <vector>
#include "End.hh"
#include "Game.hh"
#include "Menu.hh"

int main()
{
    int nbScreen;
    std::vector<Cscreen*> screens;
    std::srand(std::time(nullptr));
    sf::RenderWindow window(sf::VideoMode(/*638*/1276, 799), "Final_Game");
	window.setMouseCursorVisible(false);
    Menu menu(window.getSize().x, window.getSize().y);
    Game game(window.getSize().x, window.getSize().y, menu);
    End end(window.getSize().x, window.getSize().y);
	
    nbScreen = 0;
    screens.push_back(&menu);
    screens.push_back(&game);
    screens.push_back(&end);

    while (nbScreen != CLOSE)
    {
        nbScreen = screens[nbScreen]->Run(window);
    }

    window.close();
    return (0);
}
