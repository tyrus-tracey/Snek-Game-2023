#pragma once
/*
Board owns snake; board needs to draw snake. board needs to access individual segment loc's and col's
But, segments are private within snake class. 
*/


#include "Graphics.h"
#include "Location.h"
#include "egg.h"
#include "stageData.h"
#include <random>
#include <set>

class Board {
public:
	Board(Graphics& gfx);
	void update(const stageData& stage);
	void drawCell(const Location& loc, Color c);
	void drawCellBounds(const Location& loc, Color c);
	void initEgg(const Location& snekNextLoc);
	void drawEgg();
	void drawBorders(const stageData& stage) { drawBorders(stage.getColor()); }
	Location getEggLoc() const;
	Location getCentreLoc() const;
	int getGridWidth() const;
	int getGridHeight() const;
	int getDimension() const;
	int getWindowOffsetX() const;
	int getWindowOffsetY() const;
	bool isInBounds(const Location& loc) const;
	void setBrdLoc_Occupied(const Location& loc);
	void setBrdLoc_Vacant(const Location& loc);
	void setBrdEggInactive();
	

private:
	void initUnoccupied();
	void setBoardSize(const unsigned int h, const unsigned int w);
	void drawBorders(const Color& c);
	void calcWindowOffset();
	const Color BORDER_NORMAL = Colors::Blue;
	const Color BORDER_FLASH = Colors::Cyan;
	static constexpr int dimension = 10;
	int width=0;
	int height=0;
	int windowOffsetX = 0;
	int windowOffsetY = 0;

	Graphics& gfx;
	egg brdEgg;
	std::vector<Location> setUnoccupied;
	std::random_device rd;
	std::mt19937 rng;
};