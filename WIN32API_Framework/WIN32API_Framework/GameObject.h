#pragma once
#include "Include.h"

class GameObject
{
protected:
	Transform transform;
	float Speed;
public:
	virtual void Start()PURE;  // PURE: = 0
	virtual void Update()PURE;
	virtual void Render(HDC hdc)PURE;
	virtual void Destroy()PURE;
public:
	Transform GetTransform() { return transform; }
	//void SetTransform(Transform _transform) { transform = _transform; }  // ũ�ϱ�? �� ���� ��

	Vector3 GetPosition() { return transform.position; }
	void SetPosition(Vector3 _position) { transform.position = _position; }


public:
	GameObject();
	virtual ~GameObject();  // virtual: �޸� �����÷ο� ����
};
