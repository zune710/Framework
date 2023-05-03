#include "Bullet.h"

Bullet::Bullet()
{

}

Bullet::~Bullet()
{

}

void Bullet::Start()
{
	transform.position = Vector3(0.0f, 0.0f, 0.0f);
	transform.rotation = Vector3(0.0f, 0.0f, 0.0f);
	transform.scale = Vector3(30.0f, 30.0f, 0.0f);

	Speed = 15.0f;
}

void Bullet::Update()
{
	transform.position.x += Speed;
}

void Bullet::Render(HDC hdc)
{
	Rectangle(hdc,
		int(transform.position.x - (transform.scale.x * 0.5f)),
		int(transform.position.y - (transform.scale.y * 0.5f)),
		int(transform.position.x + (transform.scale.x * 0.5f)),
		int(transform.position.y + (transform.scale.y * 0.5f)));
}

void Bullet::Destroy()
{

}
