#pragma once

struct Location {
	Location();
	Location(const int x, const int y);
	void Add(const Location& val) {
		x += val.x;
		y += val.y;
	}
	int x;
	int y;

	bool operator==(const Location& loc) const;
	Location operator+(const Location& loc) const;
	bool operator<(const Location& loc) const;
};
