#pragma once
#include "GameObject.h"

class Player : public GameObject
{
private:
	enum STATE {IDLE, RUN, JUMP, DIVE, ROLL, ATTACK, HIT,  DIE, CLIMB};
public:
	virtual GameObject* Start()override;
	virtual int Update()override;
	virtual void Render(HDC hdc)override;
	virtual void Destroy()override;
public:
	virtual GameObject* Clone()override { return new Player(*this); }
public:
	template <typename T>
	GameObject* CreateBullet(string _Key);
	void PlayAnimation(STATE _State);
public:
	Player();
	Player(Transform _transform) : GameObject(_transform) {}
	virtual ~Player();
};

