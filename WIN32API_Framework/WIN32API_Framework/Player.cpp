#include "Player.h"
#include "Bullet.h"
#include "ObjectManager.h"
#include "InputManager.h"
#include "Prototype.h"
#include "ObjectPool.h"
#include "CollisionManager.h"

#include "NormalBullet.h"
#include "GuideBullet.h"
#include "Bitmap.h"


Player::Player() : Attack(false), Roll(false), Hit(false), Dead(false)
{

}

Player::~Player()
{

}

GameObject* Player::Start()
{
	Attack = false;
	Roll = false;
	Hit = false;
	Dead = false;

	GameOver = false;

	frame.CountX = 0;
	frame.CountY = 0;
	frame.EndFrame = 7;
	frame.FrameTime = 100;  // 0.1초
	
	transform.position = Vector3(WIDTH * 0.5f, HEIGHT * 0.5f, 0.0f);
	transform.direction = Vector3(0.0f, 0.0f, 0.0f);
	transform.scale = Vector3(679 / 7, 639 / 9, 0.0f);
	
	Speed = 5.0f;
	HP = 100;

	Key = "PlayerR";

	Time = GetTickCount64();

	return this;
}

int Player::Update()
{
	if (GameOver)
		return 0;
	
	if (Time + frame.FrameTime < GetTickCount64())
	{
		Time = GetTickCount64();
		++frame.CountX;

		if (frame.CountX == frame.EndFrame)
		{
			if (Dead)
			{
				frame.CountX = frame.EndFrame - 1;
				Dead = false;
				GameOver = true;
				return 0;
			}

			frame.CountX = 0;

			if (Attack)
				Attack = false;

			if (Roll)
				Roll = false;

			if (Hit)
				Hit = false;
		}
	}

	if (Dead)
		return 0;

	DWORD dwKey = GetSingle(InputManager)->GetKey();
	
	if (dwKey & KEYID_UP)
		transform.position.y -= Speed;

	if (dwKey & KEYID_DOWN)
		transform.position.y += Speed;

	if (dwKey & KEYID_LEFT)
	{
		transform.position.x -= Speed;
		transform.direction.x = -1.0f;
		Key = "PlayerL";
	}

	if (dwKey & KEYID_RIGHT)
	{
		transform.position.x += Speed;
		transform.direction.x = 1.0f;
		Key = "PlayerR";
	}

	if (!Hit)
	{
		if (dwKey & KEYID_SPACE)
			OnAttack();

		if (dwKey & KEYID_CONTROL)
			OnRoll();
	}

	if (!Attack && !Roll && !Hit)
	{
		if (dwKey == 0)
			SetFrame(IDLE);
		else
			SetFrame(RUN);
	}

	list<GameObject*>* EnemyList = GetSingle(ObjectManager)->GetObjectList("Enemy");
	
	if (EnemyList != nullptr && !EnemyList->empty())
		for (list<GameObject*>::iterator iter = EnemyList->begin(); iter != EnemyList->end(); ++iter)
			if (CollisionManager::CircleCollision(*iter, this))
				OnHit();

	if (HP <= 0)
		OnDie();

	return 0;
}

void Player::Render(HDC hdc)
{
	TransparentBlt(hdc,							// 복사해 넣을 그림판 ?!
		(int)transform.position.x,				// 복사할 영역 시작점 X
		(int)transform.position.y,				// 복사할 영역 시작점 Y
		(int)transform.scale.x,					// 복사할 영역 끝부분 X
		(int)transform.scale.y,					// 복사할 영역 끝부분 Y
		(*m_ImageList)[Key]->GetMemDC(),		// 복사할 이미지 (복사대상)
		int(transform.scale.x * frame.CountX),  // 복사할 시작점 X
		int(transform.scale.y * frame.CountY),  // 복사할 시작점 Y
		(int)transform.scale.x,					// 출력할 이미지의 크기만큼 X
		(int)transform.scale.y,					// 출력할 이미지의 크기만큼 Y
		RGB(255, 0, 255));						// 해당 색상을 제외
}

void Player::Destroy()
{

}

template <typename T>
GameObject* Player::CreateBullet(string _Key)
{
	GameObject* Obj = GetSingle(ObjectPool)->GetGameObject(_Key);
	Vector3 offset = Vector3(20.0f, 5.0f, 0.0f);

	if (Obj == nullptr)
	{
		Bridge* pBridge = new T;
		pBridge->Start();
		((BulletBridge*)pBridge)->SetTarget(this);

		GameObject* ProtoObj = GetSingle(Prototype)->GetGameObject(_Key);

		if (ProtoObj != nullptr)
		{
			GameObject* Object = ProtoObj->Clone();
			Object->Start();
			Object->SetPosition(transform.position + transform.scale * 0.5f + offset);
			Object->SetDirection(transform.direction);
			Object->SetKey(_Key);

			pBridge->SetObject(Object);
			Object->SetBridge(pBridge);

			return Object;
		}
		else
			return nullptr;
	}

	Obj->Start();
	Obj->SetPosition(transform.position + transform.scale * 0.5f + offset);
	Obj->SetDirection(transform.direction);
	Obj->SetKey(_Key);

	return Obj;
}

void Player::SetFrame(STATE _State)
{
	if (frame.CountY == (int)_State)
		return;

	frame.CountX = 0;
	frame.CountY = (int)_State;

	switch (_State)
	{
	case IDLE:
		frame.EndFrame = 7;
		frame.FrameTime = 100;
		break;

	case RUN:
		frame.EndFrame = 7;
		frame.FrameTime = 50;
		break;

	case JUMP:
		frame.EndFrame = 3;
		frame.FrameTime = 50;
		break;

	case DIVE:
		frame.EndFrame = 3;
		frame.FrameTime = 50;
		break;

	case ROLL:
		frame.CountX = 1;
		frame.EndFrame = 3;
		frame.FrameTime = 70;
		break;

	case ATTACK:
		frame.EndFrame = 4;
		frame.FrameTime = 100;
		break;

	case HIT:
		frame.EndFrame = 2;
		frame.FrameTime = 50;
		break;

	case DIE:
		frame.EndFrame = 5;
		frame.FrameTime = 50;
		break;

	case CLIMB:
		frame.EndFrame = 4;
		frame.FrameTime = 50;
		break;
	}
}

void Player::SetFrame(int _frame, int _locomotion, int _endFrame, float _frameTime)
{
	frame.CountX = _frame;
	frame.CountY = _locomotion;
	frame.EndFrame = _endFrame;
	frame.FrameTime = _frameTime / _endFrame;

	//IDLE: SetFrame(0, 0, 7, 150);
	//ATTACK: SetFrame(0, 5, 4, 1500);
}

void Player::OnAttack()
{
	if (Attack)
		return;

	Attack = true;
	SetFrame(ATTACK);
	//SetFrame(0, 5, 4, 1500);

	GetSingle(ObjectManager)->AddObject(CreateBullet<NormalBullet>("NormalBullet"));
}

void Player::OnRoll()
{
	if (Roll)
		return;

	Roll = true;
	SetFrame(ROLL);

	GetSingle(ObjectManager)->AddObject(CreateBullet<GuideBullet>("GuideBullet"));
}

void Player::OnHit()
{
	if (Hit)
		return;

	Hit = true;
	SetFrame(HIT);

	--HP;
}

void Player::OnDie()
{
	if (Dead)
		return;

	Dead = true;
	SetFrame(DIE);
}



