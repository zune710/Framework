#pragma once
#include "Include.h"

class MainUpdate
{
private:
	HDC m_hdc;

	RECT rcPoint;
	RECT rcPoint2;

public:
	void Start();
	void Update();
	void Render();
	void Destroy();
public:
	MainUpdate();
	~MainUpdate();
};

