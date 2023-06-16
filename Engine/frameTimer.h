#pragma once
#include <chrono>

class frameTimer
{
public:
	frameTimer();
	float getDiff();
	void updateTimePoint();
private:
	std::chrono::steady_clock::time_point last;
};

