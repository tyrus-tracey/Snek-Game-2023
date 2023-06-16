#include "Location.h"

Location::Location()
	:x(0), y(0)
{
}

Location::Location(const int x, const int y)
	: x(x), y(y)
{
}

bool Location::operator==(const Location& loc) const {
	return (loc.x == x && loc.y == y);
}

Location Location::operator+(const Location& loc) const
{
	Location output = { x,y };
	output.x += loc.x;
	output.y += loc.y;
	return output;
}

bool Location::operator<(const Location& loc) const
{
	if (x == loc.x) { return y < loc.y; }
	return x < loc.x;
}
