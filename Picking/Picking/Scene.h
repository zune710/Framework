#pragma once
#include "Include.h"

class Scene
{
public:
	virtual void Start()PURE;
	virtual void Update()PURE;
	virtual void Render(HDC _hdc)PURE;
	virtual void Destroy()PURE;
public:
	Scene();
	virtual ~Scene();
};

