#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public: // 로직 함수
	virtual void Start()override;
	virtual void Start(Vector3 _position)override {}  // 오버로드된 함수가 오버라이드됨 / Player에선 안 씀
	virtual int Update()override;
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

