/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brd(gfx),
	rnd(std::random_device()()),
	snek(brd)
{
	updateElements(getStageData());
	wnd.kbd.DisableAutorepeat();
}

void Game::updateElements(const stageData& stage)
{
	gameComplete = false;
	brd.update(stage);
	scoreboard.update(stage);
	snek.respawn(brd);
	setNormalSpeed(stage);
	readyAnimCount = 0;
	ggCount = 0;
}

void Game::Go()
{
	if (!wnd.kbd.KeyIsPressed(VK_ESCAPE)) {
		pauseKeyLockout = false;
	}
	gfx.BeginFrame();	
	if (showTitleScreen) {
		SpriteCodex::DrawTitle(gfx);
		if (wnd.kbd.KeyIsPressed(VK_RETURN)) {
			showTitleScreen = false;
		}
	}
	else {
		if (wnd.kbd.KeyIsPressed(VK_ESCAPE) && !pauseKeyLockout && !snek.isDead()) {
			togglePause();
			pauseKeyLockout = true;
		}
		if (!paused) {
			UpdateModel();
		}
		ComposeFrame();
	}
	gfx.EndFrame();
}

// Kills snake if goes beyond board or into walls.
void Game::gameCondSnakeInBrd()
{
	if (!brd.isInBounds(snek.getNextMoveLoc())) {
		snek.kill();
	}
}

// Kills snake if goes beyond the graphics window.
void Game::gameCondSnakeInGfx()
{
	if (!gfx.isInBounds(snek.getNextMoveLoc(), brd.getDimension(), brd.getWindowOffsetX(), brd.getWindowOffsetY())) {
		snek.kill();
	}
}

// Kills snake if collides with itself.
void Game::gameCondSnakeCollideSelf()
{
	if (snek.selfCollisionCheck()) {
		snek.kill();
	}
}

/*
	Reads data from the next available stage and updates game accordingly.
	If no further stage exists, the game is declared won.
*/
void Game::advanceStage()
{
	if (stageIter == stage.end() || stageIter + 1 == stage.end()) {
		gameComplete = true;
		return;
	}
	
	stageIter++;
	updateElements(*stageIter);
}

// Sets stage back to zero.
void Game::initStage()
{
	stageIter = stage.begin();
	updateElements(*stageIter);
	scoreboard.resetScores();
}

void Game::retryStage()
{
	scoreboard.resetStageScore();
	updateElements(*stageIter);
}

void Game::UpdateModel()
{
	if (gameComplete) {
		return;
	}
	if (snek.isDead() && !snek.outOfLives()) {
		if (wnd.kbd.KeyIsPressed(VK_RETURN)) {
			retryStage();
		}
	}
	updateSnakeDir();
	if (readyAnimCount <= READY_ANIM_LENGTH) {
		return;
	}
	/* 
=== Beyond here, the player is live, and the ready anim has completed. === 
	*/

	gamespeed = wnd.kbd.KeyIsPressed(VK_SPACE) ? getSpeedTurbo() : SPEED_NORMAL;

	//Enough ticks have passed to update the game? (A higher gamespeed val. means slower game)
	++frameCount;
	if (frameCount > gamespeed) {
		gameCondSnakeInBrd();
		gameCondSnakeInGfx();
		gameCondSnakeCollideSelf();
		if (!snek.isDead()) {
			if (isEggEaten()) {
				scoreboard.eggScoreIncrement();
				brd.setBrdEggInactive();
				if (scoreboard.getGoalFlag()) {
					advanceStage();
				} else {
					snek.Grow();
					brd.initEgg(snek.getNextMoveLoc());
				}
			}
			snek.Move(brd);
		}
		else {
			snek.iterateDeathAnim();
		}
		resetFrameCount(); //Tick threshold met, reset back to zero.
	}
}

void Game::updateSnakeDir()
{
	if (wnd.kbd.KeyIsPressed(VK_UP)) {
		snek.setDirection({ 0,-1 });
	}
	else if (wnd.kbd.KeyIsPressed(VK_DOWN)) {
		snek.setDirection({ 0,1 });
	}
	else if (wnd.kbd.KeyIsPressed(VK_LEFT)) {
		snek.setDirection({ -1,0 });
	}
	else if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {
		snek.setDirection({ 1,0 });
	}

}

void Game::ComposeFrame()
{
	brd.drawBorders(getStageData());
	scoreboard.displayScoreBoard(gfx, snek.getLives());
	brd.drawEgg();
	snek.draw(brd);

	if (gameComplete) {
		SpriteCodex::DrawGG(gfx);
		++ggCount;
		if (ggCount >= GG_LENGTH) {
			resetGame();
			return;
		}
	}

	if (readyAnimCount++ <= READY_ANIM_LENGTH) {
			if (readyAnimCount % 10 < 5) { //This flashes the sprite.
				SpriteCodex::DrawReady(gfx);
			}
	}
	if (snek.isDeathAnimDone()) {
		if (snek.outOfLives()) {
			SpriteCodex::DrawGameOver(gfx);
			++ggCount;
			if (ggCount >= GG_LENGTH) {
				resetGame();
			}
		}
		else {
			SpriteCodex::DrawRespawn(gfx);
			++ggCount;
			if (ggCount >= GG_LENGTH) {
				retryStage();
			}
		}
	}
	else if (paused) {
		SpriteCodex::DrawPaused(gfx);
	}
	else { 
	// At this point, game is still live.
		if (gamespeed == SPEED_NORMAL) {
			SpriteCodex::DrawBoost_Off(gfx);
		}
		else {
			SpriteCodex::DrawBoost_On(gfx);
		}
	}
	
}
