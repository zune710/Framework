#pragma once
#include "GameObject.h"

class Player : public GameObject
{
private:
	enum STATE {IDLE, RUN, JUMP, DIVE, ROLL, ATTACK, HIT,  DIE, CLIMB};

	bool Attack;
	bool Roll;

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

	void SetFrame(int _frame, int _locomotion, int _endFrame, float _frameTime);
	void OnAttack();
	void OnRoll();
public:
	Player();
	Player(Transform _transform) : GameObject(_transform), Attack(false), Roll(false) {}
	virtual ~Player();
};

