#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Start()
{
	srand((unsigned int)GetTickCount64());
	transform.position = Vector3(WIDTH + 75.0f, float(rand() % (HEIGHT - 150) + 75), 0.0f);  // 화면 안에 원 다 들어오게
	transform.rotation = Vector3(0.0f, 0.0f, 0.0f);
	transform.scale = Vector3(150.0f, 150.0f, 0.0f);

	Speed = 0.5f;
}

int Enemy::Update(Vector3 _position)
{
	transform.position.x -= Speed;

	if (transform.position.x < 0)
		return 2;

	return 0;
}

void Enemy::Render(HDC hdc)
{
	Ellipse(hdc,
		int(transform.position.x - (transform.scale.x * 0.5f)),
		int(transform.position.y - (transform.scale.y * 0.5f)),
		int(transform.position.x + (transform.scale.x * 0.5f)),
		int(transform.position.y + (transform.scale.y * 0.5f)));
}

void Enemy::Destroy()
{

}
