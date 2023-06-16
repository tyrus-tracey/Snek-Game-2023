#pragma once
#include "Graphics.h"
#include "stageData.h"
#include "SpriteCodex.h"
#include <vector>

class scoreboard
{
public:
	void update(const stageData& stage); 
	void resetScores() { totalEggScore = 0; stageEggScore = 0; }
	void resetStageScore() { totalEggScore -= stageEggScore; stageEggScore = 0; }
	void displayScoreBoard(Graphics& gfx, const int lives) const;
	void eggScoreIncrement();
	bool getGoalFlag() const { return flag_GoalReached;}
	void resetGoalFlag();

private:
	void setEggGoal(const stageData& stage);
	void initStageScore() { stageEggScore = 0; }
	bool iseggGoalReached() const { return stageEggScore >= eggGoal; }
	void drawLives(Graphics& gfx, const int lives) const;
	bool flag_GoalReached = false; //flag is used as a pseudo event-caller

	const unsigned int BOARD_SCALE = 10;
	const unsigned int BOARD_MARGIN = 2;
	const unsigned int BOARD_WRAP = 10;

	unsigned int totalEggScore = 0;
	unsigned int stageEggScore = 0;
	unsigned int eggGoal = 0;
};

