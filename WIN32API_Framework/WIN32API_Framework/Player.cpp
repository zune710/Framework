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
	transform.position = Vector3(WIDTH * 0.5f, HEIGHT * 0.5f, 0.0f);  // 정중앙
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
	// C에서는 가독성 떨어짐. C#, Java에서는 괜찮음.
	try
	{
		
		if (true)  // 에러 조건
			throw "zzz";  // try 빠져나와서 catch(string str) 또는 catch(...) 실행

		throw 10;

		throw 3.141592f;
	}
	catch (...)  // 던진 거 다 잡아옴
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
	//	// str 출력
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
