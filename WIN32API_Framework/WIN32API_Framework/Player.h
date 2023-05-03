#pragma once
#include "GameObject.h"

class Player : public GameObject
{
private:
	GameObject* BulletList[16];
public: // ���� �Լ�
	virtual void Start()override;
	virtual void Update()override;
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

