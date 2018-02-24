#include "CellProperty.hh"

CellProperty::CellProperty() :
    _walkable(false),
    _swimmable(false),
    _flyable(false),
    _event(false),
    _monster(false)
{}

CellProperty::CellProperty(CellType newCellType) :
    _walkable(false),
    _swimmable(false),
    _flyable(false),
    _event(false),
    _monster(false)
{
    if (getCellFlags(newCellType) == FLYABLE)
    {
        _flyable = true;
    }
    else if (getCellFlags(newCellType) == WALKABLE)
    {
        _walkable = true;
    }
    else if (getCellFlags(newCellType) == SWIMMABLE)
    {
        _swimmable = true;
    }
    else if (getCellFlags(newCellType) == (FLYABLE | WALKABLE))
    {
        _flyable = true;
        _walkable = true;
    }
    else if (getCellFlags(newCellType) == (SWIMMABLE | FLYABLE))
    {
        _swimmable = true;
        _flyable = true;
    }
    else if (getCellFlags(newCellType) == (SWIMMABLE | WALKABLE))
    {
        _swimmable = true;
        _walkable = true;
    }
    else if (getCellFlags(newCellType) == (SWIMMABLE | WALKABLE | FLYABLE))
    {
        _swimmable = true;
        _walkable = true;
        _flyable = true;
    }
}

bool CellProperty::isWalkable() const
{
    return (_walkable);
}
bool CellProperty::isSwimmable() const
{
    return (_swimmable);
}
bool CellProperty::isFlyable() const
{
    return (_flyable);
}
bool CellProperty::isEvent() const
{
    return (_event);
}
bool CellProperty::isMonster() const
{
    return (_monster);
}
void CellProperty::setWalkable()
{
    _walkable = true;
}
void CellProperty::setNotWalkable()
{
    _walkable = false;
}
void CellProperty::setSwimmable()
{
    _swimmable = true;
}
void CellProperty::setNotSwimmable()
{
    _swimmable = false;
}

void CellProperty::setFlyable()
{
    _flyable = true;
}

void CellProperty::setNotFlyable()
{
    _flyable = false;
}

void CellProperty::setEvent()
{
    _event = true;
}

void CellProperty::setNotEvent()
{
    _event = false;
}

void CellProperty::setMonster()
{
    _monster = true;
}

void CellProperty::setNotMonster()
{
    _monster = false;
}

int CellProperty::getCellFlags(CellType type)
{
    if (type == WaterCell)
    {
        return (SWIMMABLE | FLYABLE);
    }
    else if (type == GrassCell)
    {
        return (SWIMMABLE | WALKABLE);
    }
    else if (type == RockCell)
    {
        return (FLYABLE);
    }
    return (NO_FLAG);
}

bool operator==(CellProperty const& a, CellProperty const& b)
{
    return (a.isWalkable() == b.isWalkable() && a.isSwimmable() == b.isSwimmable()
        && a.isFlyable() == b.isFlyable() && a.isEvent() == b.isEvent()
        && a.isMonster() == b.isMonster());
}

bool operator!=(CellProperty const& a, CellProperty const& b)
{
    return (a.isWalkable() != b.isWalkable() || a.isSwimmable() != b.isSwimmable()
        || a.isFlyable() != b.isFlyable() || a.isEvent() != b.isEvent()
        || a.isMonster() != b.isMonster());
}
