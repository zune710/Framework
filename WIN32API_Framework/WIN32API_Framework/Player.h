#pragma once
#include "GameObject.h"

class Player : public GameObject
{
private:
	GameObject* BulletList[16];
public: // 로직 함수
	virtual void Start()override;
	virtual void Update()override;
	virtual void Render(HDC hdc)override;
	virtual void Destroy()override;
	// virtual, override 안 써도 가상함수 O. but 가독성 위해. override 쓰면 virtual 생략해도 됨.
	// but override 썼다고 다 가상함수는 아님.
public:  // custom 함수
	GameObject* CreateBullet();
public:
	Player();
	virtual ~Player();
};

