#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	virtual void Start()override;
	virtual void Start(Vector3 _position)override;
	virtual int Update()override { return 0; };
	virtual int Update(Transform _transform)override;
	virtual void Render(HDC hdc)override;
	virtual void Destroy()override;
public:
	bool Collision(Transform _transform);
public:
	Bullet();
	virtual ~Bullet();  // �� �ᵵ virtual ��������� ������ ����
};
