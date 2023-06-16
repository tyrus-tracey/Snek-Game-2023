#pragma once

#include "Board.h"

class Snake 
{
private:
	class Segment
	{
	public:
		Segment();
		Segment(const Location& loc);
		void kill();
		void InitHead(const Location& in_loc);
		void InitBody(const int nSegs);
		void Follow(const Segment& next);
		void MoveBy(const Location& delta_loc);
		void updateBoardLocOccupied(Board& brd, bool setOccupied);
		Location getLoc() const;
		Color getCol() const;
	private:
		Location loc;
		Color c;
	};

public:
	Snake(const Board& brd);
	void reset(const Board& brd);
	void respawn(const Board& brd);
	void kill();
	void iterateDeathAnim() { if (dead) { decay(); } }
	bool isDead() { return dead; }
	bool isDeathAnimDone() { return decayCount >= nSegments; }
	void draw(Board& brd) const;
	void Move(Board& brd);
	void Grow();
	void setDirection(Location delta_loc);
	bool selfCollisionCheck();
	bool isOccupying(const Location& loc);
	Location getLocHead() const;
	Location getLocTail() const;
	Location getDirection() const;
	Location getNextMoveLoc() const;
	int getNSegments() const;
	const int getLives() const { return lives; }
	const bool outOfLives() const { return lives <= 0; }

private:
	void MoveBy(const Location& delta_loc);
	void decay();

	//CONSTS
	const Location DEFAULT_DIRECTION{ 0,1 };
	static const int SPAWN_SIZE = 1;
	const unsigned int DEFAULT_LIVES = 5;
	static constexpr Color COL_HEAD = Colors::Yellow;
	static constexpr Color COL_BODY_ARR[6] = {
		Colors::MakeRGB(0, 255, 0),
		Colors::MakeRGB(64, 255, 0),
		Colors::MakeRGB(128, 255, 0),
		Colors::MakeRGB(191, 255, 0),
		Colors::MakeRGB(128, 255, 0),
		Colors::MakeRGB(64, 255, 0)
	};
	static constexpr Color COL_CUT = Colors::Red;
	static constexpr int nSegmentsMax = 10000;

	//VARS
	int nSegments;
	int decayCount = 0;
	unsigned int lives = DEFAULT_LIVES;
	bool dead = true;
	Segment segments[nSegmentsMax];
	Location direction{ 0,1 };
	Location spawnLoc{ 0,0 };

	
	
public:
};
