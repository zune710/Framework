#include "NormalBullet.h"
#include "Bullet.h"

NormalBullet::NormalBullet()
{
}

NormalBullet::~NormalBullet()
{
}

void NormalBullet::Start()
{
	Speed = 15.0f;
	//TargetDirection = Target->GetDirection().x;
}

void NormalBullet::Update(Transform& transform)
{
	
	transform.position += transform.direction * Speed;  //  * TargetDirection
}

void NormalBullet::Render(HDC hdc)
{
	Ellipse(hdc,
		int(Object->GetPosition().x - (Object->GetScale().x * 0.5f)),
		int(Object->GetPosition().y - (Object->GetScale().y * 0.5f)),
		int(Object->GetPosition().x + (Object->GetScale().x * 0.5f)),
		int(Object->GetPosition().y + (Object->GetScale().y * 0.5f)));
}

void NormalBullet::Destroy()
{

}
