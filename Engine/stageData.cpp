#include "stageData.h"

stageData::stageData(unsigned int w, unsigned int h, unsigned int spd, unsigned int goal, Color col)
	: width(w), height(h), speed(spd), eggGoal(goal), stageCol(col)
{
}

const unsigned int stageData::getHeight() const
{
	return height;
}

const unsigned int stageData::getWidth() const
{
	return width;
}

const unsigned int stageData::getSpeed() const
{
	return speed;
}

const unsigned int stageData::getGoal() const
{
	return eggGoal;
}

const Color stageData::getColor() const
{
	return stageCol;
}