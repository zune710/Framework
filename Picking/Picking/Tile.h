#pragma once
#include "Object.h"

class Tile : public Object
{
private:
	int check;
	int cntX, cntY;
	string Key;
public:
	virtual void Start()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Destroy()override;
public:
	Tile();
	virtual ~Tile();
};

