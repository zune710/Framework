#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	virtual void Start()override;
	virtual void Start(Vector3 _position)override;
	virtual int Update(Vector3 _position)override;
	virtual void Render(HDC hdc)override;
	virtual void Destroy()override;
public:
	Bullet();
	virtual ~Bullet();  // �� �ᵵ virtual ��������� ������ ����
};

