#include <SFML/Graphics.hpp>
#include <iostream>
#include "Attack.hh"
#include "AttackArea.hh"
#include "Hero.hh"
#include "HighlightTile.hh"
#include "PreviewAttackZone.hh"

Game::Game(unsigned int width, unsigned int height, Menu const& menu) : _width(width), _height(height), _menu(menu)
{}

Game::~Game()
{}

void Game::setMap(Map map)
{
    _map = map;
}

bool Game::canPlaceUnit(unsigned int x, unsigned int y, Unit const& unit)
{
    unsigned int i;
    UnitField field;

    i = 0;
    field = unit.getField();
    if (x >= _map.getWidth() || y >= _map.getHeight())
    {
        return (false);
    }
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

bool Game::placeUnit(Unit& unit)
{
    if (canPlaceUnit(unit.getX(), unit.getY(), unit))
    {
        _units.push_back(&unit);
        return (true);
    }
    return (false);
}

bool Game::addUnit(Unit& unit)
{
    if (unit.getOwner().getBudget() >= unit.getCost())
    {
        if (placeUnit(unit))
        {
            unit.getOwner().setBudget(unit.getOwner().getBudget() - unit.getCost());
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

void Game::cleanDeadUnits()
{
	unsigned int i;
	std::vector<unsigned int> unitsToRemove;
	std::vector<unsigned int> playersToRemove;

	/* Remove Dead Units*/
	i = 0;
	while (i < _units.size())
	{
		if (_units[i]->isDead())
		{
			unitsToRemove.push_back(i);
		}
		i++;
	}
	i = 0;
	while (i < unitsToRemove.size())
	{
		_units.erase(_units.begin() + unitsToRemove[i]);
		i++;
	}

	/* Remove Player With 0 Units*/
	i = 0;
	while (i < _players.size())
	{
		if (didLose(*_players[i]))
		{
			playersToRemove.push_back(i);
		}
		i++;
	}
	i = 0;
	while (i < playersToRemove.size())
	{
		_players.erase(_players.begin() + playersToRemove[i]);
		i++;
	}
}


void Game::newTurn()
{
	unsigned int i;

	/* Reset stats */
    i = 0;
    while (i < _units.size())
    {
        _units[i]->resetActions();
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

void Game::recalibratePosition(sf::Vector2i& pixelCoord)
{
    pixelCoord.x += 8;
    pixelCoord.y += 12;
}


void Game::convertPixelToCoord(sf::Vector2i& pixelCoord)
{
    pixelCoord.x /=  _map.getTilesize().x;
    pixelCoord.y /= _map.getTilesize().y;
}


bool Game::isReachable(sf::Vector2i coord, std::vector<sf::Vector2u> posReachable)
{
    unsigned int i;

    i = 0;
    while (i < posReachable.size())
    {
        if ((unsigned int)coord.x == posReachable[i].x && (unsigned int)coord.y == posReachable[i].y)
        {
            return (true);
        }
        i++;
    }
    return (false);
}

bool Game::askPlaceUnits(sf::RenderWindow &window, Player& player)
{
    std::string choice;
    sf::View fixed;
    sf::Texture texture;
    sf::Vector2i localPosition;
    sf::Event event_placeUnit;
    sf::Event event_selectUnit;
    std::vector<sf::Vector2u> posReachable;
    HighlightTile highlightTile;

    /* Create a fixed view */
    fixed = window.getView();

    /* Load image and create sprite */
    texture.loadFromFile("assets/image/cursorAttack.png");
    sf::Sprite cursorAttack(texture);

    /* Ask Users*/
    start:
    _chat.clear();
    _chat.addMessage("Acheter une unit:\t(Budget: " + std::to_string(player.getBudget()) + "$)", sf::Color::Black);
    _chat.addMessage("", sf::Color::White);
    _chat.addMessage("*\tT: Tank\t300$", sf::Color::Black);
    _chat.addMessage("*\tDelete: None", sf::Color::Black);
    window.clear();
    window.draw(_map);
    window.draw(_chat);
    drawItems(window);
    window.draw(_star);
    _chat.drawMessage(window);
    window.display();

    while (window.waitEvent(event_selectUnit))
    {
        if (event_selectUnit.type == sf::Event::Closed)
        {
            return (false);
        }

        else if (event_selectUnit.type == sf::Event::KeyPressed)
        {
            switch (event_selectUnit.key.code)
            {
                case sf::Keyboard::T:
                    choice = "Tank";
                    goto exit_loop;

                case sf::Keyboard::BackSpace:
                    return (true);

                case sf::Keyboard::Return:
                    return (true);

                default:
                    break;
            }
        }

        /* Window */
        window.clear();
        window.draw(_map);
        window.draw(_chat);
        drawItems(window);
        window.draw(_star);
        _chat.drawMessage(window);
        window.display();
    }

    exit_loop:
    /* Load selected area */
    if (!highlightTile.load("assets/image/selectedTile.png", sf::Vector2u(32, 32)))
    {
        return (false);
    }
    localPosition = sf::Mouse::getPosition(window);
    recalibratePosition(localPosition);
    convertPixelToCoord(localPosition);
    highlightTile.setX((unsigned int)localPosition.x);
    highlightTile.setY((unsigned int)localPosition.y);
    Tank *tmp = new Tank((unsigned int) localPosition.x, (unsigned int) localPosition.y, player);
    if (canPlaceUnit((unsigned int) localPosition.x, (unsigned int) localPosition.y, *tmp))
        highlightTile.setTileNumber(1);
    else
        highlightTile.setTileNumber(0);
    highlightTile.reload();
    free(tmp);

    /* Ask Where place Unit */
    _chat.clear();
    _chat.addMessage("Place " + choice + " ?", sf::Color::Black);
    while (window.waitEvent(event_placeUnit))
    {
        if (event_placeUnit.type == sf::Event::Closed)
        {
            return (false);
        }

        else if (event_placeUnit.type == sf::Event::KeyReleased && (event_placeUnit.key.code == sf::Keyboard::Return || event_placeUnit.key.code == sf::Keyboard::Escape || event_placeUnit.key.code == sf::Keyboard::BackSpace))
        {
            goto start;
        }

        else if (event_placeUnit.type == sf::Event::MouseMoved)
        {
            localPosition = sf::Mouse::getPosition(window);
            recalibratePosition(localPosition);
            convertPixelToCoord(localPosition);
            highlightTile.setX((unsigned int)localPosition.x);
            highlightTile.setY((unsigned int)localPosition.y);
            if (choice == "Tank")
            {
                Tank *tmp = new Tank((unsigned int) localPosition.x, (unsigned int) localPosition.y, player);
                if (canPlaceUnit((unsigned int) localPosition.x, (unsigned int) localPosition.y, *tmp))
                    highlightTile.setTileNumber(1);
                else
                    highlightTile.setTileNumber(0);
                highlightTile.reload();
                free(tmp);
            }
        }

        else if (event_placeUnit.type == sf::Event::MouseButtonReleased && event_placeUnit.mouseButton.button == sf::Mouse::Left)
        {
            if (highlightTile.getTileNumber())
            {
                localPosition = sf::Mouse::getPosition(window);
                recalibratePosition(localPosition);
                convertPixelToCoord(localPosition);
                Tank* tmp = new Tank((unsigned int)localPosition.x, (unsigned int)localPosition.y, player);
                tmp->getCost();
                if (!tmp->load("assets/image/tank.png", sf::Vector2u(32, 32)))
                    return (false);
                addUnit(*tmp);
                goto start;
            }
        }

        /* Set position */
        cursorAttack.setPosition((sf::Vector2f)(sf::Mouse::getPosition(window)));
        cursorAttack.setScale(sf::Vector2f((float)0.1, (float)0.1));

        /* Window */
        window.clear();
        window.draw(_map);
        window.draw(highlightTile);
        window.draw(_chat);
        drawItems(window);
        window.draw(_star);
        _chat.drawMessage(window);
        window.setView(fixed);
        window.draw(cursorAttack);
        window.display();
    }
    return (false);
}

sf::Vector2i Game::askAttack(sf::RenderWindow &window, Unit const& unit)
{
	sf::View fixed;
	sf::Texture texture;
    sf::Vector2i localPosition;
    sf::Event event;
    AttackArea attackArea;
    HighlightTile highlightTile;
    PreviewAttackZone previewAttackZone;
    std::vector<sf::Vector2u> posReachable;
    std::vector<sf::Vector2u> posColateral;

	/* Create a fixed view */
	fixed = window.getView();

	/* Load image and create sprite */
	texture.loadFromFile("assets/image/cursorAttack.png");
	sf::Sprite cursorAttack(texture);

    /* Load area reachable */
    posReachable = getPosReachable(unit);
    if (!attackArea.load(unit, "assets/image/areaReachable.png", sf::Vector2u(32, 32), posReachable))
    {
        return (sf::Vector2i(-1, -1));
    }

    /* Load selected area */
    if (!highlightTile.load("assets/image/selectedTile.png", sf::Vector2u(32, 32)))
    {
        return (sf::Vector2i(-1, -1));
    }
    localPosition = sf::Mouse::getPosition(window);
    recalibratePosition(localPosition);
    convertPixelToCoord(localPosition);
    highlightTile.setX((unsigned int)localPosition.x);
    highlightTile.setY((unsigned int)localPosition.y);
    if (isReachable(localPosition, posReachable))
    {
        highlightTile.setTileNumber(1);
        posColateral = getColateral((unsigned int)localPosition.x, (unsigned int)localPosition.y, unit);
        previewAttackZone.load(unit, "assets/image/previewAttack.png", sf::Vector2u(32, 32), posColateral);
    }
    else
        highlightTile.setTileNumber(0);
    highlightTile.reload();

    /* Main loop */
    while (window.waitEvent(event))
    {
        if (event.type == sf::Event::Closed)
	    {
	        return (sf::Vector2i(-2, -2));
	    }

        else if (event.type == sf::Event::MouseMoved)
        {
            localPosition = sf::Mouse::getPosition(window);
            recalibratePosition(localPosition);
            convertPixelToCoord(localPosition);
            highlightTile.setX((unsigned int)localPosition.x);
            highlightTile.setY((unsigned int)localPosition.y);
            if (isReachable(localPosition, posReachable))
                highlightTile.setTileNumber(1);
            else
                highlightTile.setTileNumber(0);
            posColateral = getColateral((unsigned int)localPosition.x, (unsigned int)localPosition.y, unit);
            previewAttackZone.load(unit, "assets/image/previewAttack.png", sf::Vector2u(32, 32), posColateral);
            highlightTile.reload();
        }

        else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            if (highlightTile.getTileNumber())
            {
                localPosition = sf::Mouse::getPosition(window);
                recalibratePosition(localPosition);

                return (localPosition);
            }
            _chat.addMessage("Attack: out of range", sf::Color::Red);
        }

        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        {
            return (sf::Vector2i(-1, -1));
        }

		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
		{
			return (sf::Vector2i(-1, -1));
		}

        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace)
        {
            return (sf::Vector2i(-1, -1));
        }

		/* Set position */       
		cursorAttack.setPosition((sf::Vector2f)(sf::Mouse::getPosition(window)));
		cursorAttack.setScale(sf::Vector2f((float)0.1, (float)0.1));

		/* Window */
		window.clear();
		window.draw(_map);
        window.draw(attackArea);
        if (highlightTile.getTileNumber())
            window.draw(previewAttackZone);
        window.draw(highlightTile);
        window.draw(_chat);
        drawItems(window);
		window.draw(_star);
        _chat.drawMessage(window);
		window.setView(fixed);
		window.draw(cursorAttack);
        window.display();
    }
    return (sf::Vector2i(-1, -1));
}


void Game::moveUnit(Unit& unit, Direction direction, unsigned int n)
{
    unsigned int i;
    unsigned int j;
    unsigned tmp_x;
    unsigned tmp_y;
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

std::vector<sf::Vector2u> Game::getPosReachable(Unit const& unit)
{
    unsigned int i;
    unsigned int j;
    std::vector<sf::Vector2u> posReachable;

    i = 0;
    while (i < _map.getWidth())
    {
        j = 0;
        while (j < _map.getHeight())
        {
            if (Map::getDistanceBetween(unit.getX(), unit.getY(), i, j) <= unit.getAttackArea() && _map.canGo(i, j, unit))
            {
                posReachable.emplace_back(sf::Vector2u(i, j));
            }
            j++;
        }
        i++;
    }
    return (posReachable);
}

std::vector<sf::Vector2u> Game::getColateral(unsigned int x, unsigned int y, Unit const& unit)
{
    unsigned int i;
    unsigned int j;
    UnitField field;
    std::vector<sf::Vector2u> posColateral;

    i = 0;
    while (i < _map.getWidth())
    {
        j = 0;
        while (j < _map.getHeight())
        {
            if (Map::getDistanceBetween(i, j, x, y) >= unit.getAttackMinRange() && Map::getDistanceBetween(i, j, x, y) <= unit.getAttackRange()) // y en haut
            {
                posColateral.emplace_back(sf::Vector2u(i, j));
            }
            j++;
        }
        i++;
    }
    return (posColateral);
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
        else if (Map::getDistanceBetween(_units[i]->getX(), _units[i]->getY(), x, y) >= rangeMin && Map::getDistanceBetween(_units[i]->getX(), _units[i]->getY(), x, y) <= rangeMax)
        {
            inRange.push_back(_units[i]);
        }
        i++;
    }
    return (inRange);
}


void Game::initPlayers()
{
    int i;
	unsigned int j;
    sf::VertexArray vertices;
    sf::Texture tileset;
    std::vector<Unit*> tmp_units;

    i = 0;
    while (i < _menu.getSelectedItem() + 2)
    {
        _players.push_back(new Player((unsigned int)i + 1, 10000));
        i++;
    }

    j = 0;
    while (j < _players.size())
    {
        tmp_units.push_back(new Hero(std::rand() % _map.getWidth() + 0, std::rand() % _map.getHeight() + 0, *_players[j]));

        while (!addUnit(*tmp_units[j]))
        {
            tmp_units[j]->setX(std::rand() % _map.getWidth() + 0);
            tmp_units[j]->setY(std::rand() % _map.getWidth() + 0);
        }
        j++;
    }

    j = 0;
    while (j < _units.size())
    {
        _units[j]->resetStats();
        j++;
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

bool Game::loadUnits(const std::string& tileset, sf::Vector2u tileSize)
{
    unsigned int i;

    i = 0;
    while (i < _units.size())
    {
        if (!_units[i]->load(tileset, tileSize))
        {
            return (false);
        }
        i++;
    }
    return (true);
}

bool Game::reloadItems()
{
    unsigned int i;

    i = 0;
    while (i < _units.size())
    {
        if (!_units[i]->reload())
        {
            return (false);
        }
        i++;
    }

    _star.reload();
    return (true);
}

int Game::Run(sf::RenderWindow &window)
{
    int numUnits;
	sf::Vector2i targetPosition;
    sf::Sound musicGong;
	sf::Sound musicMovePlayer;
    sf::SoundBuffer bufferMusicGong;
	sf::SoundBuffer bufferMusicMovePlayer;
	const std::string pathChat              = "assets/image/chat.png";
    const std::string pathMusicGong         = "assets/music/game/gong.ogg";
    const std::string pathMusicMovePlayer   = "assets/music/game/move/player.wav";
    const std::string pathImageMap          = "assets/image/Map.png";
    const std::string pathImageSprite       = "assets/image/Sprite.png";
    const std::string pathImageStar         = "assets/image/star.png";

    /* Init */
    numUnits = 0;
    initPlayers();

    /* Load */
    if (!bufferMusicGong.loadFromFile(pathMusicGong) || !bufferMusicMovePlayer.loadFromFile(pathMusicMovePlayer))
    {
        return (CLOSE);
    }
	musicMovePlayer.setBuffer(bufferMusicMovePlayer);
	musicMovePlayer.setVolume(10);
    musicGong.setBuffer(bufferMusicGong);
	musicGong.setVolume(20);
    musicGong.play();
    if (!_map.load(pathImageMap, sf::Vector2u(32, 32), _map.getWidth(), _map.getHeight()))
    { 
        return (CLOSE);
    }
    if (!loadUnits(pathImageSprite, sf::Vector2u(32, 32)))
    {
        return (CLOSE);
    }
	if (!_chat.load(pathChat, sf::Vector2u(532, 161), _map, window))
	{
		return (CLOSE);
	}

    /* Star Position */
    _star.setX(_units[numUnits]->getX());
    _star.setY(_units[numUnits]->getY() - 1);
    if (!_star.load(pathImageStar, sf::Vector2u(32, 32)))
    {
        return (CLOSE);
    }

    /* Ask Each Player to Place Unit */
    unsigned long capturePlayersSize = _players.size();
    while (numUnits < capturePlayersSize)
    {
        _star.setX(_units[numUnits]->getX());
        _star.setY(_units[numUnits]->getY() - 1);
        _star.reload();
        if (!askPlaceUnits(window, _units[numUnits]->getOwner()))
            return (CLOSE);
        numUnits++;
    }
    numUnits = 0;
    resetUnits();
    _chat.clear();
    _chat.addMessage("Le combat commence", sf::Color::Black);

    /* Main Loop Game*/
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
                // Move
                case sf::Keyboard::Up:
					_units[numUnits]->turn(North);
                    moveUnit(*_units[numUnits], North, 1);
					musicMovePlayer.play();
		            break;
		    
                case sf::Keyboard::Down:
					_units[numUnits]->turn(South);
                    moveUnit(*_units[numUnits], South, 1);
					musicMovePlayer.play();
                    break;
		    
                case sf::Keyboard::Left:
					_units[numUnits]->turn(East);
                    moveUnit(*_units[numUnits], East, 1);
					musicMovePlayer.play();
                    break;
		    
                case sf::Keyboard::Right:
					_units[numUnits]->turn(West);
                    moveUnit(*_units[numUnits], West, 1);
					musicMovePlayer.play();
                    break;

                // Attack
				case sf::Keyboard::Return:
					targetPosition = askAttack(window, *_units[numUnits]);
                    if (targetPosition.x >= 0)
                    {
                        convertPixelToCoord(targetPosition);
                        Attack attack(*this, *_units[numUnits]);
                        attack.perform((unsigned int)targetPosition.x, (unsigned int)targetPosition.y);
                    }
                    else if (targetPosition.x == (-2))
                        return (CLOSE);
					break;


                // Skip Turn
				case sf::Keyboard::BackSpace:
					_chat.addMessage(_units[numUnits]->getOwner().getName() + " passe son tour", sf::Color::Yellow);
					numUnits++;
					break;

                default:
                    break;
            }
        }

		/* Check Win */
        cleanDeadUnits();
        if (_players.size() == 1)
		{
			_chat.addMessage(_players[0]->getName() + " Wins !!!", sf::Color::Magenta);
			return (END);
		}
        else if (_players.empty())
		{
			std::cout << "Tie!!!" << std::endl;
			return (END);
		}

        /* Check New Turn */
		if (numUnits == _units.size())
		{
			numUnits = 0;
			newTurn();
		}

        /* Update Star Position */
        _star.setX(_units[numUnits]->getX());
        _star.setY(_units[numUnits]->getY() - 1);

        /* Window */
		_units[numUnits]->printInfo();
        reloadItems();
        window.clear();
        window.draw(_map);
		window.draw(_chat);
        drawItems(window);
		window.draw(_star);
		_chat.drawMessage(window);
        window.display();
    }
    return (CLOSE);
}

Chat &Game::getChat()
{
    return (_chat);
}
