/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Game.h"
#include "Board.h"
#include "Snake.h"
#include "scoreboard.h"
#include "stageData.h"
#include "frameTimer.h"
#include <random>

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
	
private:
	void ComposeFrame();
	void UpdateModel();
	
	/********************************/
	/*  User Functions              */
	void resetGame() { showTitleScreen = true; initStage(); ggCount = 0; snek.reset(brd); }
	void updateSnakeDir();
	void gameCondSnakeInBrd(); //exceeds board borders -> kill
	void gameCondSnakeInGfx(); //exceeds graphics window -> kill
	void gameCondSnakeCollideSelf(); //hits self -> kill
	void resetFrameCount() { frameCount = 0; }
	const stageData getStageData() const { return *stageIter; }
	void advanceStage();
	void initStage();
	void retryStage();
	void setNormalSpeed(const stageData& stage) { SPEED_NORMAL = stage.getSpeed();}
	void updateElements(const stageData& stage);
	int getSpeedTurbo() const { return SPEED_NORMAL / 2; }
	bool isEggEaten() const { return snek.getNextMoveLoc() == brd.getEggLoc(); }
	void togglePause() { paused = paused ? false : true; }
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	Board brd;
	std::mt19937 rnd;
	Snake snek;
	scoreboard scoreboard;

	static const int STAGE_WAIT_TIME = 120;

	unsigned int SPEED_NORMAL;
	unsigned int gamespeed;
	unsigned int frameCount = 0;
	bool showTitleScreen = true;
	bool gameComplete = false;
	bool paused = false;
	const unsigned int READY_ANIM_LENGTH= 60;
	unsigned int readyAnimCount = 0;
	unsigned int readyAnimInterval = 0;
	const unsigned int GG_LENGTH = 500;
	unsigned int ggCount = 0;
	bool pauseKeyLockout = true;

	// Width, Height, Speed, Goal
	const std::vector<stageData> stage{
		stageData(14, 14, 30, 5, Colors::MakeRGB(unsigned char(0),unsigned char(38),unsigned char(125))),
		stageData( 10,  10,  8, 10, Colors::MakeRGB(unsigned char(265),unsigned char(165),unsigned char(0))),
		stageData( 5,  8, 10,  9, Colors::Magenta),
		stageData(60, 24,  2, 30, Colors::White),
		stageData(10, 10,  6, 30, Colors::MakeRGB(unsigned char(203),unsigned char(27),unsigned char(0))),
	};
	std::vector<stageData>::const_iterator stageIter = stage.begin();
	
	
	/********************************/
};