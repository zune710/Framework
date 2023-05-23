#include "Player.h"
#include "Bullet.h"
#include "ObjectManager.h"
#include "InputManager.h"
#include "Prototype.h"

Player::Player()
{

}

Player::~Player()
{

}

GameObject* Player::Start()
{
	transform.position = Vector3(WIDTH * 0.5f, HEIGHT * 0.5f, 0.0f);  // ���߾�
	transform.direction = Vector3(0.0f, 0.0f, 0.0f);
	transform.scale = Vector3(100.0f, 100.0f, 0.0f);

	Speed = 5.0f;

	return this;
}

int Player::Update()
{
	
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
	{
		GetSingle(ObjectManager)->AddObject(CreateBullet());
	}

	return 0;
}

void Player::Render(HDC hdc)
{
	Rectangle(hdc,
		int(transform.position.x - (transform.scale.x * 0.5f)),
		int(transform.position.y - (transform.scale.y * 0.5f)),
		int(transform.position.x + (transform.scale.x * 0.5f)),
		int(transform.position.y + (transform.scale.y * 0.5f)));
}

void Player::Destroy()
{

}

GameObject* Player::CreateBullet()
{
	GameObject* ProtoObj = GetSingle(Prototype)->GetGameObject("Bullet");

	/*
	// C������ ������ ������. C#, Java������ ������.
	try
	{
		
		if (true)  // ���� ����
			throw "zzz";  // try �������ͼ� catch(string str) �Ǵ� catch(...) ����

		throw 10;

		throw 3.141592f;
	}
	catch (...)  // ���� �� �� ��ƿ�
	{

	}
	//catch (int n)
	//{

	//}
	//catch (float f)
	//{

	//}
	//catch (string str)
	//{
	//	// str ���
	//}
	*/

	if (ProtoObj != nullptr)
	{
		GameObject* Object = ProtoObj->Clone();
		Object->Start();
		Object->SetPosition(transform.position);
		return Object;
	}
	else
		return nullptr;
}
