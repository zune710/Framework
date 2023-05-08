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

	Transform GetTransform()const { return transform; } // const ����ϸ� ���������� �� ���� �Ұ�. �б� ����.: transform.position = transform.scale; (X)

	Vector3 GetPosition()const { return transform.position; }
	void SetPosition(const Vector3& _position) { transform.position = _position; }  // _position �� ���� �Ұ�

	Vector3 GetScale()const { return transform.scale; }
	void SetScale(const Vector3& _scale) { transform.scale = _scale; }
public:
	GameObject();
	virtual ~GameObject();
};
