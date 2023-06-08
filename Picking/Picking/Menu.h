#pragma once
#include "Scene.h"

class Menu : public Scene
{
public:
	virtual void Start()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Destroy()override;
public:
	Menu();
	virtual ~Menu();
};

