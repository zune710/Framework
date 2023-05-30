#pragma once
#include "Include.h"

class Timer
{
public:
	Single(Timer)
private:
	double frequency;
	double previous;
	double current;
	double timeScale;
	double deltaTime;
public:
	void Update();
	double GetDeltaTime() { return deltaTime; }
private:
	Timer();
public:
	~Timer();
};

