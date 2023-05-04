#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public: // ���� �Լ�
	virtual void Start()override;
	virtual void Start(Vector3 _position)override {}  // �����ε�� �Լ��� �������̵�� / Player���� �� ��
	virtual int Update()override;
	virtual void Render(HDC hdc)override;
	virtual void Destroy()override;
	// virtual, override �� �ᵵ �����Լ� O. but ������ ����. override ���� virtual �����ص� ��.
	// but override ��ٰ� �� �����Լ��� �ƴ�.
public:  // custom �Լ�
	GameObject* CreateBullet();
public:
	Player();
	virtual ~Player();
};

