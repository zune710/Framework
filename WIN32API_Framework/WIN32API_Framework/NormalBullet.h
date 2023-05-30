#pragma once
#include "BulletBridge.h"

class NormalBullet : public BulletBridge
{
private:
	float TargetDirection;
public:
	virtual void Start()override;
	virtual void Update(Transform& transform)override;
	virtual void Render(HDC hdc)override;
	virtual void Destroy()override;
public:
	NormalBullet();
	virtual ~NormalBullet();
};

