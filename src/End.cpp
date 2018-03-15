//
// Created by Acal HABI on 14/03/2018.
//

#include "End.hh"
#include "Menu.hh"

End::End(unsigned int width, unsigned int height)
{
    if (_font.loadFromFile("assets/font/dpcomic.ttf"))
    {
        _message.setFont(_font);
        _message.setFillColor(sf::Color::Red);
        _message.setString("Game Over");
        _message.setPosition(sf::Vector2f(width / 2, height / 2));
    }
}

End::~End()
{}

void End::draw(sf::RenderWindow &window)
{
    window.draw(_message);
}

int End::Run(sf::RenderWindow &window)
{
    window.clear();
    draw(window);
    window.display();

    sf::Event event;
    while (window.waitEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            return (CLOSE);
        }
        if (event.type == sf::Event::KeyPressed)
        {
            return (CLOSE);
        }
        window.clear();
        draw(window);
        window.display();
    }
    return (CLOSE);
}