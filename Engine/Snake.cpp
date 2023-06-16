#include "Snake.h"
Snake::Snake(const Board& brd)
	: spawnLoc(brd.getCentreLoc())
{
	respawn(brd);
}

void Snake::respawn(const Board& brd)
{
	if (lives <= 0) { return; }
	decayCount = 0;
	nSegments = SPAWN_SIZE;
	segments[0].InitHead(brd.getCentreLoc());
	direction = DEFAULT_DIRECTION;
	dead = false;
}

void Snake::reset(const Board& brd)
{
	lives = DEFAULT_LIVES;
	respawn(brd);
}

void Snake::kill()
{
	if (dead) {return;}
	direction = { 0,0 };
	dead = true;
	lives--;
}

void Snake::draw(Board& brd) const
{
	for (int i = nSegments - 1; i >= 0; --i) {
		brd.drawCellBounds(segments[i].getLoc(), segments[i].getCol());
	}
}

/*
	Moves head, and segments to follow. Updates vacancies for head and tail segments.
*/
void Snake::Move(Board& brd)
{
	segments[nSegments - 1].updateBoardLocOccupied(brd, false); //set old tail pos as vacant
	Snake::MoveBy(Snake::direction);
	segments[0].updateBoardLocOccupied(brd, true); //set new head pos as occupied
}

void Snake::MoveBy(const Location& delta_loc)
{
	for (int n = nSegments - 1; n > 0; --n) {
		segments[n].Follow(segments[n - 1]);
	}
	segments[0].MoveBy(delta_loc);
}

// Increments segment kill.
void Snake::decay()
{
	if (decayCount < nSegments) {
		segments[decayCount].kill();
		decayCount++;
	}
}

void Snake::Grow()
{
	if (nSegments < nSegmentsMax) {
		nSegments++;
		segments[nSegments - 1].InitBody(nSegments);
		segments[nSegments-1].Follow(segments[nSegments-2]);
	}
}

void Snake::setDirection(Location delta_loc)
{
	// Ensure delta is at most 1 position
	if (abs(delta_loc.x) + abs(delta_loc.y) > 1) {
		if (delta_loc.x > delta_loc.y) {
			delta_loc = Location(1, 0);
		}
		else {
			delta_loc = Location(0, 1);
		}
	}
	// Ensure snake can't go backwards into itself
	if (nSegments >= 2) {
		if (Snake::getLocHead() + delta_loc == segments[1].getLoc()) {
			return;
		}
	}
	Snake::direction = delta_loc;
}

Location Snake::getLocHead() const
{
	return segments[0].getLoc();
}

Snake::Segment::Segment()
{
	c = Snake::COL_BODY_ARR[0];
}

Snake::Segment::Segment(const Location& in_loc)
{
	c = Snake::COL_BODY_ARR[0];
	loc = in_loc;
}

void Snake::Segment::kill()
{
	c = Colors::Red;
}

void Snake::Segment::InitHead(const Location& in_loc)
{
	loc = in_loc;
	c = Snake::COL_HEAD;
}

void Snake::Segment::InitBody(const int nSegs) {
	
	c = COL_BODY_ARR[(nSegs-1) % 6];
}

void Snake::Segment::Follow(const Segment& next) {
	loc = next.loc;
}

void Snake::Segment::MoveBy(const Location& delta_loc) {
	
	loc.Add(delta_loc);
}

/*
	Adds or removes segment location to Board setUnoccupied, depending on bool arg.
*/
void Snake::Segment::updateBoardLocOccupied(Board& brd, bool setOccupied)
{
	if (setOccupied) { brd.setBrdLoc_Occupied(this->loc); }
	else { brd.setBrdLoc_Vacant(this->loc);}
	return;
}

/*
	Checks whether next move will collide into any segment.
*/
bool Snake::selfCollisionCheck()
{
	//Location nextLoc = getLocHead() + direction;
	Location nextLoc = getLocHead();
	for (int i = 1; i < nSegments; ++i) {
		if (segments[i].getLoc() == nextLoc) {
			return true;
		}
	}
	return false;
}

/*
	Checks if any segment is occupying the specified location.
*/
bool Snake::isOccupying(const Location& loc)
{
	for (int i = 0; i < nSegments; ++i) {
		if (segments[i].getLoc() == loc) {
			return true;
		}
	}
	return false;
}

Location Snake::getLocTail() const
{
	return segments[nSegments-1].getLoc();
}

Location Snake::getDirection() const
{
	return direction;
}

// Returns head location + current direction (i.e. upcoming move).
Location Snake::getNextMoveLoc() const
{
	return getLocHead() + getDirection();
}

int Snake::getNSegments() const
{
	return nSegments;
}

Location Snake::Segment::getLoc() const
{
	return loc;
}

Color Snake::Segment::getCol() const
{
	return c;
}
