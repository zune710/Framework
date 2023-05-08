#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public: // ���� �Լ�
	virtual GameObject* Start()override;
	virtual int Update()override;
	virtual void Render(HDC hdc)override;
	virtual void Destroy()override;
public:  // custom �Լ�
	GameObject* CreateBullet();
public:
	Player();
	virtual ~Player();
};

