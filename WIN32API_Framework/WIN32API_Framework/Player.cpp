#include "Player.h"
#include "Bullet.h"
#include "ObjectManager.h"
#include "InputManager.h"
#include "Prototype.h"
#include "ObjectPool.h"

#include "NormalBullet.h"
#include "GuideBullet.h"
#include "Bitmap.h"



Player::Player()
{

}

Player::~Player()
{

}

GameObject* Player::Start()
{
	frame.CountX = 0;
	frame.CountY = 0;
	frame.EndFrame = 7;
	frame.FrameTime = 50;  // 0.05초
	
	transform.position = Vector3(WIDTH * 0.5f, HEIGHT * 0.5f, 0.0f);  // 정중앙
	transform.direction = Vector3(0.0f, 0.0f, 0.0f);
	transform.scale = Vector3(679 / 7, 639 / 9, 0.0f);

	Speed = 5.0f;

	Key = "Player";

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
			frame.CountX = 0;
	}

	DWORD dwKey = GetSingle(InputManager)->GetKey();

	if (dwKey & KEYID_UP)
		transform.position.y -= Speed;

	if (dwKey & KEYID_DOWN)
		transform.position.y += Speed;

	if (dwKey & KEYID_LEFT)
		transform.position.x -= Speed;

	if (dwKey & KEYID_RIGHT)
		transform.position.x += Speed;
	
	if (dwKey & KEYID_SPACE)
		GetSingle(ObjectManager)->AddObject(CreateBullet<NormalBullet>("NormalBullet"));

	if (dwKey & KEYID_CONTROL)
		GetSingle(ObjectManager)->AddObject(CreateBullet<GuideBullet>("GuideBullet"));


	if (dwKey == 0)
		PlayAnimation(IDLE);
	else if ((dwKey & KEYID_SPACE) || (dwKey & KEYID_CONTROL))
		PlayAnimation(ATTACK);
	else
		PlayAnimation(RUN);

	return 0;
}

void Player::Render(HDC hdc)
{
	TransparentBlt(hdc,					   // 복사해 넣을 그림판 ?!
		(int)transform.position.x,		   // 복사할 영역 시작점 X
		(int)transform.position.y,		   // 복사할 영역 시작점 Y
		(int)transform.scale.x,			   // 복사할 영역 끝부분 X
		(int)transform.scale.y,			   // 복사할 영역 끝부분 Y
		(*m_ImageList)[Key]->GetMemDC(),   // 복사할 이미지 (복사대상)
		transform.scale.x * frame.CountX,  // 복사할 시작점 X
		transform.scale.y * frame.CountY,  // 복사할 시작점 Y
		(int)transform.scale.x,			   // 출력할 이미지의 크기만큼 X
		(int)transform.scale.y,			   // 출력할 이미지의 크기만큼 Y
		RGB(255, 0, 255));				   // 해당 색상을 제외
	
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
			Object->SetPosition(transform.position + transform.scale * 0.5f);
			Object->SetKey(_Key);

			pBridge->SetObject(Object);
			Object->SetBridge(pBridge);

			return Object;
		}
		else
			return nullptr;
	}
	
	Obj->Start();
	Obj->SetPosition(transform.position + transform.scale * 0.5f);
	Obj->SetKey(_Key);

	return Obj;
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
		break;
	case RUN:
		frame.EndFrame = 7;
		break;
	case JUMP:
		break;
	case DIVE:
		break;
	case ROLL:
		break;
	case ATTACK:
		frame.EndFrame = 4;
		break;
	case HIT:
		break;
	case DIE:
		break;
	case CLIMB:
		break;
	}
}

