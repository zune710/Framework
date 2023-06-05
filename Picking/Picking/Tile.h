#pragma once
#include "Object.h"

class Tile : public Object
{
private:
	int hor;
	int ver;
public:
	virtual void Start()override;
	virtual int Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Destroy()override;
public:
	int GetHorizontal()const { return hor; }
	void SetHorizontal(const int& _hor) { hor = _hor; }
public:
	Tile();
	virtual ~Tile();
};

