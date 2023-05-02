#include "Player.h"

Player::Player()
{

}

Player::~Player()
{

}

void Player::Start()
{
	// private 아닌 protected여야 transform 사용 가능, position 등이 포인터여야 유니티처럼 new 가능
	transform.position = new Vector3(700.0f, 350.0f, 0.0f);  // 창 대략 가운데 지점
	transform.rotation = new Vector3(0.0f, 0.0f, 0.0f);
	transform.scale = new Vector3(100.0f, 100.0f, 0.0f);
}

void Player::Update()
{
	if (GetAsyncKeyState(VK_UP))
		transform.position->y -= 5.0f;

	if (GetAsyncKeyState(VK_DOWN))
		transform.position->y += 5.0f;

	if (GetAsyncKeyState(VK_LEFT))
		transform.position->x -= 5.0f;

	if (GetAsyncKeyState(VK_RIGHT))
		transform.position->x += 5.0f;
}

void Player::Render(HDC hdc)
{
	Rectangle(hdc,
		int(transform.position->x - (transform.scale->x * 0.5f)),  // '*0.5f' == '/2'
		int(transform.position->y - (transform.scale->y * 0.5f)),
		int(transform.position->x + (transform.scale->x * 0.5f)),
		int(transform.position->y + (transform.scale->y * 0.5f)));
}

void Player::Destroy()
{

}
