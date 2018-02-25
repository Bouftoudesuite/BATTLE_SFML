#ifndef _GAME_HH_
# define _GAME_HH_

#include <SFML/Graphics.hpp> 
#include <SFML/Audio.hpp>
#include <vector>
#include "Cscreen.hh"
#include "Map.hh"
#include "Menu.hh"
#include "Unit.hh"
#include "Player.hh"
#include "Direction.hh"

class Game : public Cscreen
{
public:
    Game(unsigned int width, unsigned int height, Menu const& menu);
    ~Game();
    void setMap(Map map);
    void initPlayers();
    bool canPlaceUnit(int x, int y, Unit const& unit);
    bool placeUnit(Unit* unit);
    bool addUnit(Unit* unit);
    void resetUnits();
    void newTurn();
    bool didLose(Player const& player);
	void convertPixelToCoord(sf::Vector2i& pixelCoord);
	static sf::Vector2i askPosition(sf::RenderWindow &window);
    void moveUnit(Unit& unit, Direction direction, unsigned int n);
    std::vector<Unit*> getInRange(unsigned int x, unsigned int y, unsigned int rangeMin, unsigned int rangeMax, UnitField field);
    bool loadUnits(const std::string& tileset, sf::Vector2u tileSize, int width, int height);
    bool reloadUnits(const std::string& tileset, sf::Vector2u tileSize, int width, int height);
    void drawItems(sf::RenderWindow &window);
    int Run(sf::RenderWindow &window) override;
private:
    unsigned int _width;
    unsigned int _height;
    Map _map;
	Menu const& _menu;
    std::vector<Player*> _players;
    std::vector<Unit*> _units;
};

#endif /*_GAME_HH_*/
