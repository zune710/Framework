#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public: // 로직 함수
	virtual GameObject* Start()override;
	virtual int Update()override;
	virtual void Render(HDC hdc)override;
	virtual void Destroy()override;
public:  // custom 함수
	GameObject* CreateBullet();
public:
	Player();
	virtual ~Player();
};

