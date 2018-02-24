#ifndef _CASTLE_HH_
# define _CASTLE_HH_

#include <string>

class Castle
{
public:
    explicit Castle(std::string const& name);
    int getNbTowers() const;
    const std::string& getName() const;
    void SetNbTowers(int nbTowers);
    void CloseGates();
    void CloseGates(int nbDoors);
private:
    int _nbTowers;
    const std::string _name;
};

bool operator==(Castle const& a, Castle const& b);
bool operator!=(Castle const& a, Castle const& b);
bool operator>(Castle const& a, Castle const& b);
bool operator<(Castle const& a, Castle const& b);
bool operator>=(Castle const& a, Castle const& b);
bool operator<=(Castle const& a, Castle const& b);

#endif
