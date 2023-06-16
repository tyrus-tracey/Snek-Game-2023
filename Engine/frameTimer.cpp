#include "frameTimer.h"

frameTimer::frameTimer()
{
	updateTimePoint();
}

void frameTimer::updateTimePoint()
{
	last = std::chrono::steady_clock::now();
}

float frameTimer::getDiff()
{
	std::chrono::duration<float> output = std::chrono::steady_clock::now() - last;
	return output.count();
}



