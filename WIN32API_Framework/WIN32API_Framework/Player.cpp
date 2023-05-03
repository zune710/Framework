#include "Player.h"
#include "Bullet.h"

Player::Player()
{

}

Player::~Player()
{

}

void Player::Start()
{
	// private 아닌 protected여야 transform 사용 가능, position 등이 포인터여야 유니티처럼 new 가능
	transform.position = Vector3(700.0f, 350.0f, 0.0f);
	transform.rotation = Vector3(0.0f, 0.0f, 0.0f);
	transform.scale = Vector3(100.0f, 100.0f, 0.0f);

	Speed = 5.0f;

	for (int i = 0; i < 16; ++i)
		BulletList[i] = nullptr;
	// NULL: 0
	// nullptr: null포인터
}

void Player::Update()
{
	for (int i = 0; i < 16; ++i)
		if (BulletList[i] != nullptr)
			BulletList[i]->Update();
	
	if (GetAsyncKeyState(VK_UP))
		transform.position.y -= Speed;

	if (GetAsyncKeyState(VK_DOWN))
		transform.position.y += Speed;

	if (GetAsyncKeyState(VK_LEFT))
		transform.position.x -= Speed;

	if (GetAsyncKeyState(VK_RIGHT))
		transform.position.x += Speed;

	if (GetAsyncKeyState(VK_SPACE))
	{
		for (int i = 0; i < 16; ++i)
		{
			if (BulletList[i] == nullptr)
			{
				BulletList[i] = CreateBullet();
				break;
			}
		}
	}
}

void Player::Render(HDC hdc)
{
	Rectangle(hdc,
		int(transform.position.x - (transform.scale.x * 0.5f)),
		int(transform.position.y - (transform.scale.y * 0.5f)),
		int(transform.position.x + (transform.scale.x * 0.5f)),
		int(transform.position.y + (transform.scale.y * 0.5f)));

	for (int i = 0; i < 16; ++i)
		if (BulletList[i] != nullptr)
			BulletList[i]->Render(hdc);
}

void Player::Destroy()
{

}

GameObject* Player::CreateBullet()
{
	GameObject* bullet = new Bullet();
	bullet->Start();
	bullet->SetPosition(transform.position);

	return bullet;
}
