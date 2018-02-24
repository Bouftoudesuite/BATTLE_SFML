#include <SFML/Graphics.hpp> 
#include <SFML/Audio.hpp>
#include "Game.hh"
#include "Menu.hh"
#include <ctime>

int main()
{
    int action;
    std::srand(std::time(nullptr));
    sf::RenderWindow window(sf::VideoMode(638, 638), "Final_Game");

    Menu menu(window.getSize().x, window.getSize().y);
    action = menu.Run(window);

    if (action == PLAY)
    {
        Game game(window.getSize().x, window.getSize().y, menu.getSelectedItem() + 2);
        game.Run(window);
    }

    window.close();
    return (0);
}
