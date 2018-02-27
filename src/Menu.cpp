#include "Menu.hh"

Menu::Menu(unsigned int width, unsigned int height)
{
    if (_font.loadFromFile("assets/font/arial.ttf"))
    {
        _selectedItemIndex = 0;
        _title.setFont(_font);
        _title.setFillColor(sf::Color::Yellow);
        _title.setString("Mode de Jeu:");
        _title.setPosition(sf::Vector2f(width / 2, height / (MAX_PLAYER + 1) * 1 * 3/4));
        _menu[0].setFont(_font);
        _menu[0].setFillColor(sf::Color::Red);
        _menu[0].setString("2 Joueurs");
        _menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_PLAYER + 1) * 2 * 3/4));
        _menu[1].setFont(_font);
        _menu[1].setFillColor(sf::Color::White);
        _menu[1].setString("3 Joueurs");
        _menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_PLAYER + 1) * 3 * 3/4));
        _menu[2].setFont(_font);
        _menu[2].setFillColor(sf::Color::White);
        _menu[2].setString("4 Joueurs");
        _menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_PLAYER + 1) * 4 * 3/4));
        _menu[3].setFont(_font);
        _menu[3].setFillColor(sf::Color::White);
        _menu[3].setString("5 Joueurs");
        _menu[3].setPosition(sf::Vector2f(width / 2, height / (MAX_PLAYER + 1) * 5 * 3/4));
        _menu[4].setFont(_font);
        _menu[4].setFillColor(sf::Color::White);
        _menu[4].setString("6 Joueurs");
        _menu[4].setPosition(sf::Vector2f(width / 2, height / (MAX_PLAYER + 1) * 6 * 3/4));
        _menu[5].setFont(_font);
        _menu[5].setFillColor(sf::Color::White);
        _menu[5].setString("7 Joueurs");
        _menu[5].setPosition(sf::Vector2f(width / 2, height / (MAX_PLAYER + 1) * 7 * 3/4));
        _menu[6].setFont(_font);
        _menu[6].setFillColor(sf::Color::White);
        _menu[6].setString("8 Joueurs");
        _menu[6].setPosition(sf::Vector2f(width / 2, height / (MAX_PLAYER + 1) * 8 * 3/4));
    }
}

Menu::~Menu()
{}

int Menu:: getSelectedItem() const
{
    return (_selectedItemIndex);
}


void Menu::draw(sf::RenderWindow &window)
{
    int i;

    i = 0;
    window.draw(_title);
    while (i < MAX_PLAYER)
    {
        window.draw(_menu[i]);
        i++;
    }
}

void Menu::MoveUp()
{
    _menu[_selectedItemIndex].setFillColor(sf::Color::White);
    if (_selectedItemIndex - 1 >= 0)
    {
        _selectedItemIndex--;
    }
    else
    {
        _selectedItemIndex = MAX_PLAYER - 1;
    }
    _menu[_selectedItemIndex].setFillColor(sf::Color::Red);
}

void Menu::MoveDown()
{
    _menu[_selectedItemIndex].setFillColor(sf::Color::White);
    if (_selectedItemIndex + 1 < MAX_PLAYER)
    {
        _selectedItemIndex++;
    }
    else
    {
        _selectedItemIndex = 0;
    }
    _menu[_selectedItemIndex].setFillColor(sf::Color::Red);
}

int Menu::Run(sf::RenderWindow &window)
{
    sf::Music menuMusic;
    sf::Sound menuMove;
    sf::Sound menuSelect;
    sf::SoundBuffer bufferMenuMove;
    sf::SoundBuffer bufferMenuSelect;
    const std::string pathMusicMenuMove = "assets/music/menu/move.ogg";
    const std::string pathMusicMenuSelect = "assets/music/menu/select.ogg";
	
    if (!bufferMenuMove.loadFromFile(pathMusicMenuMove) || !bufferMenuSelect.loadFromFile(pathMusicMenuSelect))
    {
        return (CLOSE);
    }
    menuMusic.setLoop(true);
    menuMove.setBuffer(bufferMenuMove);
    menuSelect.setBuffer(bufferMenuSelect);

    sf::Event event;
    while (window.waitEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            return (CLOSE);
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
                case sf::Keyboard::Up:
		    menuMove.play();
                    MoveUp();
                    break;

                case sf::Keyboard::Down:
		    menuMove.play();
                    MoveDown();
                    break;

                case sf::Keyboard::Return:
		    menuSelect.play();
                    return (PLAY);
                
                default:
                    break;
            }
        }
	
        window.clear();
        draw(window);
        window.display();
    }
    return (CLOSE);
}
