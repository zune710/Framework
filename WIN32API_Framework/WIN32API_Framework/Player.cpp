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


Player::Player() : Attack(false), Roll(false), Hit(false)
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
	frame.FrameTime = 50;  // 0.05��
	
	transform.position = Vector3(WIDTH * 0.5f, HEIGHT * 0.5f, 0.0f);  // ���߾�
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

			if (Hit)
				Hit = false;
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

	return 0;
}

void Player::Render(HDC hdc)
{
	TransparentBlt(hdc,							// ������ ���� �׸��� ?!
		(int)transform.position.x,				// ������ ���� ������ X
		(int)transform.position.y,				// ������ ���� ������ Y
		(int)transform.scale.x,					// ������ ���� ���κ� X
		(int)transform.scale.y,					// ������ ���� ���κ� Y
		(*m_ImageList)[Key]->GetMemDC(),		// ������ �̹��� (������)
		int(transform.scale.x * frame.CountX),  // ������ ������ X
		int(transform.scale.y * frame.CountY),  // ������ ������ Y
		(int)transform.scale.x,					// ����� �̹����� ũ�⸸ŭ X
		(int)transform.scale.y,					// ����� �̹����� ũ�⸸ŭ Y
		RGB(255, 0, 255));						// �ش� ������ ����
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
	frame.FrameTime = _frameTime;
}

void Player::OnAttack()
{
	if (Attack)
		return;

	Attack = true;
	SetFrame(ATTACK);

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
}



