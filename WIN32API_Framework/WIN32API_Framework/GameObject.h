#pragma once
#include "Include.h"

class GameObject
{
protected:
	Transform transform;
	float Speed;

	string Key;
public:
	virtual GameObject* Start()PURE;
	virtual int Update()PURE;
	virtual void Render(HDC hdc)PURE;
	virtual void Destroy()PURE;
public:
	string GetKey()const { return Key; }

	Transform GetTransform()const { return transform; } // const 사용하면 직접적으로 값 변경 불가. 읽기 전용.: transform.position = transform.scale; (X)

	Vector3 GetPosition()const { return transform.position; }
	void SetPosition(const Vector3& _position) { transform.position = _position; }  // _position 값 변경 불가

	Vector3 GetScale()const { return transform.scale; }
	void SetScale(const Vector3& _scale) { transform.scale = _scale; }
public:
	GameObject();
	virtual ~GameObject();
};
