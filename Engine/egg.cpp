#include "egg.h"

egg::egg()
	: loc({0,0}), col(Colors::White)
{
}

egg::egg(Location spawnLoc)
	: loc(spawnLoc), col(Colors::White)
{
}

egg::egg(Location spawnLoc, Color eggColor)
	: loc(spawnLoc), col(eggColor)
{
}


Location egg::getLoc() const {
	return loc;
}

void egg::setLoc(const Location& newLoc) {
	loc = newLoc;
}

Color egg::getCol() const
{
	return col;
}