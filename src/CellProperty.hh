#ifndef _CELLPROPERTY_HH_
# define _CELLPROPERTY_HH_

#include "CellType.hh"

#define NO_FLAG 0
#define FLYABLE 1
#define WALKABLE 2
#define SWIMMABLE 4

class CellProperty
{
public:
    CellProperty();
    static int getCellFlags(CellType type);
    explicit CellProperty(CellType newCellType);
    bool isWalkable() const;
    bool isSwimmable() const;
    bool isFlyable() const;
    bool isEvent() const;
    bool isMonster() const;
    void setWalkable();
    void setNotWalkable();
    void setSwimmable();
    void setNotSwimmable();
    void setFlyable();
    void setNotFlyable();
    void setEvent();
    void setNotEvent();
    void setMonster();
    void setNotMonster();
private:
    bool _walkable;
    bool _swimmable;
    bool _flyable;
    bool _event;
    bool _monster;
};

bool operator==(CellProperty const& a, CellProperty const& b);
bool operator!=(CellProperty const& a, CellProperty const& b);

#endif
