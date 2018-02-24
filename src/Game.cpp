#include <iostream>
#include "Game.hh"
#include "Hero.hh"
#include "Menu.hh"

Game::Game(unsigned int width, unsigned int height, unsigned int nbPlayer) : _width(width), _height(height), _nbPlayer(nbPlayer)
{}

Game::~Game()
{}

unsigned int Game::getNbPlayer() const
{
    return (_nbPlayer);
}

void Game::setMap(Map map)
{
    _map = map;
}

bool Game::canPlaceUnit(int x, int y, Unit const& unit)
{
    unsigned int i;
    UnitField field;

    i = 0;
    field = unit.getField();
    while (i < _units.size())
    {
        if (_units[i]->getField() == field && _units[i]->getX() == x && _units[i]->getY() == y)
        {
            return (false);
        }
        i++;
    }
    return (_map.canGo(x, y, unit));
}

bool Game::placeUnit(Unit* unit)
{
    if (canPlaceUnit(unit->getX(), unit->getY(), *unit))
    {
        _units.push_back(unit);
        return (true);
    }
    return (false);
}

bool Game::addUnit(Unit* unit)
{
    if (unit->getOwner().getBudget() >= unit->getCost())
    {
        if (placeUnit(unit))
        {
            unit->getOwner().setBudget(unit->getOwner().getBudget() - unit->getCost());
            return (true);
        }
    }
    return (false);
}

void Game::resetUnits()
{
    unsigned int i;

    i = 0;
    while (i < _units.size())
    {
        _units[i]->resetStats();
        i++;
    }
}

void Game::newTurn()
{
    std::vector<int> toRemove;
    unsigned int i;

    i = 0;
    while (i < _units.size())
    {
        if (_units[i]->getHp() <= 0)
        {
            toRemove.push_back(i - 1);
        }
        i++;
    }

    i = 0;
    while (i < toRemove.size())
    {
        _units.erase(_units.begin() + toRemove[i]);
        i++;
    }

    i = 0;
    while (i < _units.size())
    {
        _units[i]->resetStats();
        i++;
    }
}

bool Game::didLose(Player const& player)
{
    unsigned int i;

    i = 0;
    while (i < _units.size())
    {
        if (_units[i]->getOwner().getName() == player.getName())
        {
            return (false);
        }
        i++;
    }
    return (true);
}

void Game::moveUnit(Unit& unit, Direction direction, unsigned int n)
{
    unsigned int i;
    unsigned int j;
    int tmp_x;
    int tmp_y;
    bool stop;

    i = 0;
    j = 0;
    stop = false;
    tmp_x = unit.getX();
    tmp_y = unit.getY();

    while (i < n)
    {
        switch (direction)
	{
	    case North:
	        tmp_y -= 1;
		break;

	    case South:
	        tmp_y += 1;
		break;

	    case East:
	        tmp_x -= 1;
		break;

	    case West:
		tmp_x += 1;
		break;
	}

        while (j < _units.size())
        {
            if (_units[j]->getOwner().getName() != unit.getOwner().getName() && _units[j]->getField() == unit.getField()
                && _units[j]->getX() == tmp_x && _units[j]->getY() == tmp_y && !stop)
            {
                std::cout << "message: invalid move: enemy in the way" << std::endl;
                stop = true;
            }
            else if (!_map.canGo(tmp_x, tmp_y, unit) && !stop)
            {
                std::cout << "invalid move: no path" << std::endl;
                stop = true;
            }
            j++;
        }

        i++;
    }

    if (unit.getMp() < n && !stop)
    {
        std::cout << "invalid move: mp" << std::endl;
    }
    else if ((tmp_x < 0 || tmp_y < 0) && !stop)
    {
        std::cout << "invalid move: oob" << std::endl;
    }
    else if (!canPlaceUnit(tmp_x, tmp_y, unit) && !stop)
    {
        std::cout << "invalid move: cell occupied" << std::endl;
    }
    else if (!stop)
    {
        unit.setMp(unit.getMp() - n);
        unit.setX(tmp_x);
        unit.setY(tmp_y);
    }
}

std::vector<Unit*> Game::getInRange(unsigned int x, unsigned int y, unsigned int rangeMin, unsigned int rangeMax, UnitField field)
{
    unsigned int i;
    std::vector<Unit*> inRange;

    i = 0;
    while (i < _units.size())
    {
        if (rangeMax < rangeMin)
        {
            std::cout << "invalid range" << std::endl;
        }
        else if (((_units[i]->getX() >= x + rangeMin && _units[i]->getX() <= x + rangeMax) // x en bas
                    || (_units[i]->getX() <= x - rangeMin && _units[i]->getX() >= x - rangeMax))  // x en haut
                 && ((_units[i]->getY() >= y + rangeMin && _units[i]->getY() <= y + rangeMax) // y en bas
                    || (_units[i]->getY() <= y - rangeMin && _units[i]->getY() >= y - rangeMax))  // y en haut
                 && _units[i]->getField() == field) // field
        {
            inRange.push_back(_units[i]);
        }
        i++;
    }
    return (inRange);
}


void Game::initPlayers()
{
    unsigned int i;
    sf::VertexArray vertices;
    sf::Texture tileset;
    std::vector<Unit*> tmp_units;

    i = 0;
    while (i < getNbPlayer())
    {
        _players.push_back(new Player(i + 1, 10000));
        i++;
    }

    i = 0;
    while (i < _players.size())
    {
        tmp_units.push_back(new Hero(std::rand() % _map.getWidth() + 0, std::rand() % _map.getHeight() + 0, *_players[i]));

        while (!addUnit(tmp_units[i]))
        {
            tmp_units[i]->setX(std::rand() % _map.getWidth() + 0);
            tmp_units[i]->setY(std::rand() % _map.getWidth() + 0);
        }
        i++;
    }

    i = 0;
    while (i < _units.size())
    {
        _units[i]->resetStats();
        i++;
    }
}

void Game::drawItems(sf::RenderWindow &window)
{
    unsigned int i;

    i = 0;
    while (i < _units.size())
    {
        window.draw(*_units[i]);
        i++;
    }
}

bool Game::loadUnits(const std::string& tileset, sf::Vector2u tileSize, int width, int height)
{
    unsigned int i;

    i = 0;
    while (i < _units.size())
    {
        if (!_units[i]->load(tileset, sf::Vector2u(32, 32), _map.getWidth(), _map.getHeight()))
        {
            return (false);
        }
        i++;
    }
    return (true);
}

bool Game::reloadUnits(const std::string& tileset, sf::Vector2u tileSize, int width, int height)
{
    unsigned int i;

    i = 0;
    while (i < _units.size())
    {
        if (!_units[i]->reload(tileset, sf::Vector2u(32, 32), _map.getWidth(), _map.getHeight()))
        {
            return (false);
        }
        i++;
    }
    return (true);
}

int Game::Run(sf::RenderWindow &window)
{
    int numPlayer;
    int numUnits;
	sf::Sound gong;
	sf::SoundBuffer bufferGong;
	const std::string pathImageMap = "assets/image/Map.png";
	const std::string pathImageSprite = "assets/image/Sprite.png";
	const std::string pathMusicGong = "assets/music/game/gong.ogg";

	numPlayer = 0;
    numUnits = 0;
    initPlayers();
    
	if (!bufferGong.loadFromFile(pathMusicGong))
	{
		return (CLOSE);
	}
	gong.setBuffer(bufferGong);
	gong.play();

    if (!_map.load(pathImageMap, sf::Vector2u(32, 32), _map.getWidth(), _map.getHeight()))
    {
        return (CLOSE);
    }
    if (!loadUnits(pathImageSprite, sf::Vector2u(32, 32), _map.getWidth(), _map.getHeight()))
    {
        return (CLOSE);
    }

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
                    moveUnit(*_units[numUnits], North, 1);
                    _units[numUnits]->turn(North);
					break;
                case sf::Keyboard::Down:
                    moveUnit(*_units[numUnits], South, 1);
                    _units[numUnits]->turn(South);
                    break;
                case sf::Keyboard::Left:
                    moveUnit(*_units[numUnits], East, 1);
                    _units[numUnits]->turn(East);
                    break;
                case sf::Keyboard::Right:
                    moveUnit(*_units[numUnits], West, 1);
                    _units[numUnits]->turn(West);
                    break;
                default:
                    break;
            }
        }

        if (_units[numUnits]->getMp() <= 0)
        {
            numUnits++;
        }
        if (numUnits == _players.size())
        {
            numUnits = 0;
            newTurn();
        }

        reloadUnits(pathImageSprite, sf::Vector2u(32, 32), _map.getWidth(), _map.getHeight());
        window.clear();
        window.draw(_map);
        drawItems(window);
        window.display();
    }
    return (CLOSE);
}
