#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	void Start()override;
	void Update()override;
	void Render(HDC hdc)override;
	void Destroy()override;
public:
	Bullet();
	virtual ~Bullet();  // 안 써도 virtual 적용되지만 가독성 위해
};

