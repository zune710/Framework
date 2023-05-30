#include "Timer.h"

Timer::Timer() : current(0), timeScale(0), deltaTime(0)
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

	QueryPerformanceCounter((LARGE_INTEGER*)&previous);

	timeScale = 1 / frequency;
}

Timer::~Timer()
{
}

void Timer::Update()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&current);
	
	deltaTime = (current - previous) * timeScale;
	previous = current;
}
