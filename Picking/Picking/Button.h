#pragma once
#include "Object.h"

class Button : public Object
{
public:
	virtual void Start()override;
	virtual int Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Destroy()override;
public:
	Button();
	virtual ~Button();
};

