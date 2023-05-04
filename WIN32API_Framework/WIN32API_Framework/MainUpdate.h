#pragma once
#include "Include.h"

class GameObject;
class MainUpdate
{
private:
	HDC m_hdc;
public:
	void Start();
	void Update();
	void Render();
	void Destroy();
public:
	MainUpdate();
	~MainUpdate();
};

