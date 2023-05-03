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

void Bullet::Start(Vector3 _position)
{
	transform.position = _position;
	transform.rotation = Vector3(0.0f, 0.0f, 0.0f);
	transform.scale = Vector3(30.0f, 30.0f, 0.0f);

	Speed = 15.0f;
}

int Bullet::Update(Transform _transform)
{
	transform.position.x += Speed;

	if (transform.position.x > WIDTH)
		return 1;

	//Enemy Ãæµ¹
	if (Collision(_transform))
		return 1;

	return 0;
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


bool Bullet::Collision(Transform _transform)  // Enemy transform
{
	RECT rc = {
		int(transform.position.x - (transform.scale.x * 0.5f)),
		int(transform.position.y - (transform.scale.y * 0.5f)),
		int(transform.position.x + (transform.scale.x * 0.5f)),
		int(transform.position.y + (transform.scale.y * 0.5f)) };
	
	int x = _transform.position.x;
	int y = _transform.position.y;
	int radius = int(_transform.scale.x * 0.5);
	int left = rc.left;
	int right = rc.right;
	int top = rc.top;
	int bottom = rc.bottom;
	
	if ((left <= x && x < right) || (top <= y && y < bottom))
	{
		if ((y + radius > top) && (y - radius < bottom)
			&& (x + radius > left) && (x - radius < right))
			return true;
	}
	else
	{
		int rt = (x - right) * (x - right) + (y - top) * (y - top);
		int rb = (x - right) * (x - right) + (y - bottom) * (y - bottom);
		int lt = (x - left) * (x - left) + (y - top) * (y - top);
		int lb = (x - left) * (x - left) + (y - bottom) * (y - bottom);
			
		
		if (((sqrt((double)rt) <= radius) && (x >= right && y <= top))
			|| ((sqrt((double)rb) <= radius) && (x >= right && y >= bottom))
			|| ((sqrt((double)lt) <= radius) && (x <= left && y <= top))
			|| ((sqrt((double)lb) <= radius) && (x <= left && y >= bottom)))
			return true;
	}
	return false;
}
