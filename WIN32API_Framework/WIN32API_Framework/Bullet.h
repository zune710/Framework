#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	virtual void Start()override;
	virtual void Start(Vector3 _position)override;
	virtual int Update()override;
	virtual void Render(HDC hdc)override;
	virtual void Destroy()override;
public:
	bool Collision(Transform _transform);
public:
	Bullet();
	virtual ~Bullet();  // 안 써도 virtual 적용되지만 가독성 위해
};

