#pragma once
#include "Include.h"

class GameObject;
class Bridge
{
protected:
	GameObject* Object;
public:
	virtual void Start()PURE;
	virtual void Update(Transform& transform)PURE;  // 변경되어야 하므로 const 안 넣음
	virtual void Render(HDC hdc)PURE;
	virtual void Destroy()PURE;
public:
	void SetObject(GameObject* _Object) { Object = _Object; }
public:
	Bridge() : Object(nullptr) {}
	virtual ~Bridge() {}
};