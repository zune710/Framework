#include "GuideBullet.h"
#include "GameObject.h"

GuideBullet::GuideBullet()
{
}

GuideBullet::~GuideBullet()
{
}

void GuideBullet::Start()
{
	Speed = 2.5f;
}

void GuideBullet::Update(Transform& transform)
{
	float Horizontal = (Target->GetPosition().x + Target->GetScale().x * 0.5f) - transform.position.x;
	float Vertical = (Target->GetPosition().y + Target->GetScale().y * 0.5f) - transform.position.y;

	float value = (Horizontal * Horizontal) + (Vertical * Vertical);
	float Distance = (float)sqrt((double)value);

	Vector3 Direction;

	if (Distance != 0)
	{
		Direction = Vector3(
			Horizontal / Distance,
			Vertical / Distance,
			0.0f);
	}
	else
		Direction = Vector3(0.0f, 0.0f, 0.0f);
	
	transform.position += Direction * Speed;
}

void GuideBullet::Render(HDC hdc)
{
	Ellipse(hdc,
		int(Object->GetPosition().x - (Object->GetScale().x * 0.5f)),
		int(Object->GetPosition().y - (Object->GetScale().y * 0.5f)),
		int(Object->GetPosition().x + (Object->GetScale().x * 0.5f)),
		int(Object->GetPosition().y + (Object->GetScale().y * 0.5f)));
}

void GuideBullet::Destroy()
{

}
