#ifndef _END_HH_
#define _END_HH_

#include <SFML/Graphics.hpp>
#include "Cscreen.hh"

class End : public Cscreen
{
public:
    End(unsigned int width, unsigned int height);
    ~End();
    void draw(sf::RenderWindow &window);
    int Run (sf::RenderWindow &window) override;
private:
    sf::Font _font;
    sf::Text _message;
};


#endif //_END_HH_
