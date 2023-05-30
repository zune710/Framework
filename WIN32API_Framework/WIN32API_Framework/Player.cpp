#include "Player.h"
#include "Bullet.h"
#include "ObjectManager.h"
#include "InputManager.h"
#include "Prototype.h"
#include "ObjectPool.h"

#include "NormalBullet.h"
#include "GuideBullet.h"
#include "Bitmap.h"


Player::Player() : Attack(false), Roll(false)
{

}

Player::~Player()
{

}

GameObject* Player::Start()
{
	Attack = false;


	frame.CountX = 0;
	frame.CountY = 0;
	frame.EndFrame = 7;
	frame.FrameTime = 50;  // 0.05초
	
	transform.position = Vector3(WIDTH * 0.5f, HEIGHT * 0.5f, 0.0f);  // 정중앙
	transform.direction = Vector3(0.0f, 0.0f, 0.0f);
	transform.scale = Vector3(679 / 7, 639 / 9, 0.0f);
	
	Speed = 5.0f;

	Key = "PlayerR";

	Time = GetTickCount64();

	return this;
}

int Player::Update()
{
	if (Time + frame.FrameTime < GetTickCount64())
	{
		Time = GetTickCount64();

		++frame.CountX;

		if (frame.CountX == frame.EndFrame)
		{
			frame.CountX = 0;

			if (Attack)
				Attack = false;

			if (Roll)
				Roll = false;
		}
	}

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

	if (dwKey & KEYID_SPACE)
		OnAttack();

	if (dwKey & KEYID_CONTROL)
		OnRoll();

	if (!Attack && !Roll)
	{
		if (dwKey == 0)
		{
			if(frame.CountY != 0)
				SetFrame(0, 0, 7, 50);
		}
		else
		{
			if(frame.CountY != 1)
				SetFrame(0, 1, 7, 50);
		}
	}

	/*if (!Attack && !Roll)
	{
		if (dwKey == 0)
			PlayAnimation(IDLE);
		else
			PlayAnimation(RUN);
	}*/

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

	/*
	Rectangle(hdc,
		int(transform.position.x - (transform.scale.x * 0.5f)),
		int(transform.position.y - (transform.scale.y * 0.5f)),
		int(transform.position.x + (transform.scale.x * 0.5f)),
		int(transform.position.y + (transform.scale.y * 0.5f)));
	*/
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

void Player::SetFrame(int _frame, int _locomotion, int _endFrame, float _frameTime)
{
	frame.CountX = _frame;
	frame.CountY = _locomotion;
	frame.EndFrame = _endFrame;
	frame.FrameTime = _frameTime;
}

void Player::OnAttack()
{
	if (Attack)
		return;

	Attack = true;
	SetFrame(0, 5, 4, 100);

	GetSingle(ObjectManager)->AddObject(CreateBullet<NormalBullet>("NormalBullet"));
}

void Player::OnRoll()
{
	if (Roll)
		return;

	Roll = true;
	SetFrame(1, 4, 3, 70);

	GetSingle(ObjectManager)->AddObject(CreateBullet<GuideBullet>("GuideBullet"));
}


void Player::PlayAnimation(STATE _State)
{
	if (frame.CountY == (int)_State)
		return;

	frame.CountX = 0;
	frame.CountY = (int)_State;

	switch (_State)
	{
	case IDLE:
		frame.EndFrame = 7;
		frame.FrameTime = 50;
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
		Roll = false;
		frame.EndFrame = 5;
		frame.FrameTime = 50;
		break;

	case ATTACK:
		Attack = false;
		frame.EndFrame = 4;
		frame.FrameTime = 60;
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

