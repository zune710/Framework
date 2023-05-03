#pragma once
#include "Include.h"

class GameObject
{
protected:
	Transform transform;
	float Speed;
public:
	virtual void Start()PURE;  // PURE: = 0
	virtual void Start(Vector3 _position)PURE;
	virtual int Update(Vector3 _position)PURE;
	virtual void Render(HDC hdc)PURE;
	virtual void Destroy()PURE;
public:
	Transform GetTransform() { return transform; }
	//void SetTransform(Transform _transform) { transform = _transform; }  // 크니까? 안 씀

	Vector3 GetPosition() { return transform.position; }
	void SetPosition(Vector3 _position) { transform.position = _position; }


public:
	GameObject();
	virtual ~GameObject();  // virtual: 메모리 오버플로우 방지
};
