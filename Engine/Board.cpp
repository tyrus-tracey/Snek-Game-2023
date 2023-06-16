#include <assert.h>
#include <algorithm>
#include "Board.h"

Board::Board(Graphics& gfx)
	: gfx(gfx), rng(std::random_device()())
{
	calcWindowOffset();
}

void Board::update(const stageData& stage)
{
	setBoardSize(stage.getHeight(), stage.getWidth());
	calcWindowOffset();
	initUnoccupied();
	initEgg({-1,-1});
}

/*
	Clears and adds all board locations to setUnoccupied vector, minus the centre where Snek spawns.
*/
void Board::initUnoccupied()
{
	setUnoccupied.clear();
	Location l;
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			l = { x,y };
			setUnoccupied.push_back(l);
		}
	}
	setBrdLoc_Occupied(getCentreLoc());
}

void Board::drawCell(const Location& loc, Color c)
{
	gfx.DrawRectDim(
		loc.x * dimension + windowOffsetX,
		loc.y * dimension + windowOffsetY,
		dimension, dimension, c
	);
}

// Only draws if cell is within borders.
void Board::drawCellBounds(const Location& loc, Color c)
{
	if (isInBounds(loc)) {
		gfx.DrawRectDim(
			loc.x * dimension + windowOffsetX,
			loc.y * dimension + windowOffsetY,
			dimension, dimension, c
		);
	}
}

/* 
	Picks randomly from the board's unoccupied locations to be the egg's location.
	Re-rolls once if egg lands on the board edge to reduce bad luck.
	Also re-rolls if lands on snek's immediate next location to reduce good luck ;)
*/
void Board::initEgg(const Location& snekNextLoc)
{
	int numOpenLocs = int(setUnoccupied.size());
	if (numOpenLocs <= 0) {
		return;
	}

	std::uniform_int_distribution<int> locIndexRange(0, numOpenLocs - 1);
	Location eggLoc = setUnoccupied[locIndexRange(rng)];
	
	if (eggLoc == Location(0,0) || 
		eggLoc == Location(width-1, height-1)||
		eggLoc == snekNextLoc
		) {
		eggLoc = setUnoccupied[locIndexRange(rng)];
	}
	brdEgg.setLoc(eggLoc);
}

void Board::drawEgg()
{
	drawCellBounds(brdEgg.getLoc(), brdEgg.getCol());
	return;
}

void Board::drawBorders(const Color& c)
{
	for (int x = -1; x <= width; x++) {
		drawCell({ x, -1 }, c);
		drawCell({ x, height }, c);
	}
	for (int y = -1; y <= height; y++) {
		drawCell({ -1, y }, c);
		drawCell({ width,y }, c);
	}
}

/*
	Caches the midpoint of the graphics window.
*/
void Board::calcWindowOffset()
{
	windowOffsetX = (gfx.ScreenWidth - dimension * width) / 2;
	windowOffsetY = (gfx.ScreenHeight - dimension * height) / 2;
}

Location Board::getEggLoc() const
{
	return brdEgg.getLoc();
}

Location Board::getCentreLoc() const
{
	int x = width / 2;
	int y = height / 2;
	if (x < 0) { x = 0; }
	if (y < 0) { y = 0; }
	return { x,y };
}

int Board::getGridWidth() const
{
	return width;
}

int Board::getGridHeight() const
{
	return height;
}

int Board::getDimension() const
{
	return dimension;
}

int Board::getWindowOffsetX() const
{
	return windowOffsetX;
}

int Board::getWindowOffsetY() const
{
	return windowOffsetY;
}

bool Board::isInBounds(const Location& loc) const
{
	if (loc.x < 0 ||
		loc.y < 0 ||
		loc.x >= width ||
		loc.y >= height 
		) {
		return false;
	}
	
	return true;
}

/*
	Removes specified location from setUnoccupied vector, if it exists.
*/
void Board::setBrdLoc_Occupied(const Location& loc)
{
	std::vector<Location>::iterator target = std::find(setUnoccupied.begin(), setUnoccupied.end(), loc);
	if (target != setUnoccupied.end()){
		setUnoccupied.erase(target);
	}
}

/*
	Adds specified location to setUnoccupied vector, if not already present.
*/
void Board::setBrdLoc_Vacant(const Location& loc)
{
	std::vector<Location>::iterator target = std::find(setUnoccupied.begin(), setUnoccupied.end(), loc);
	if (target == setUnoccupied.end()){
		setUnoccupied.push_back(loc);
	}
	std::sort(setUnoccupied.begin(), setUnoccupied.end());

}

// Sets egg outside of board.
void Board::setBrdEggInactive()
{
	brdEgg.setLoc({-1,-1});
}

void Board::setBoardSize(const unsigned int h, const unsigned int w)
{
	height = h;
	width = w;
}
