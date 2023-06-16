#pragma once
#include "Location.h"
#include "Colors.h"

class egg {
public:
	egg();
	egg(Location spawnLoc);
	egg(Location spawnLoc, Color eggColor);
	Location getLoc() const;
	void setLoc(const Location& newLoc);
	Color getCol() const;


private:
	Location loc;
	Color col;
};