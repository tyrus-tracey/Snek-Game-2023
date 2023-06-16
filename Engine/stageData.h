#pragma once
#include "Colors.h"
/*
	Describes board size, board color, game speed, and the target egg goal.
*/
class stageData
{
public:
	stageData(	unsigned int w, 
				unsigned int h, 
				unsigned int spd, 
				unsigned int goal,
				Color col);
	const unsigned int getHeight() const;
	const unsigned int getWidth() const;
	const unsigned int getSpeed() const;
	const unsigned int getGoal() const;
	const Color getColor() const;
private:
	unsigned int height;
	unsigned int width;
	unsigned int speed;
	unsigned int eggGoal;
	Color stageCol;
};

