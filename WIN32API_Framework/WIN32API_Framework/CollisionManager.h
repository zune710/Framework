#pragma once
#include "GameObject.h"

class CollisionManager
{
public:
	// ** 구(동그라미) 충돌
	static bool CircleCollision(GameObject* temp, GameObject* dest)  //temp = current, dest = target
	{
		// ** x값과 y값을 구한다.
		float fx = dest->GetPosition().x - temp->GetPosition().x;  // 방향성을 갖는다.(dest로 가는 방향)
		float fy = dest->GetPosition().y - temp->GetPosition().y;

		// ** 각각의 구의 반지름의 합을 구한다.
		float sum = (dest->GetScale().x + temp->GetScale().x) * 0.5f;


		// ** 거리를 구한다.
		float value = (fx * fx) + (fy * fy);
		float distance = (float)sqrt((double)value);

		// ** 거리가 반지름의 합보다 작다면 충돌
		if (distance < sum)
			return true;

		return false;
	}

	// ** Rect 충돌
	static bool RectCollision(GameObject* temp, GameObject* dest)
	{
		// ** 각각의 Rect 상, 하, 좌, 우 좌표를 비교하여 충돌을 확인
		if (temp->GetPosition().x + (temp->GetScale().x * 0.5f) > dest->GetPosition().x - (dest->GetScale().x * 0.5f) &&
			dest->GetPosition().x + (dest->GetScale().x * 0.5f) > temp->GetPosition().x - (temp->GetScale().x * 0.5f) &&
			temp->GetPosition().y + (temp->GetScale().y * 0.5f) > dest->GetPosition().y - (dest->GetScale().y * 0.5f) &&
			dest->GetPosition().y + (dest->GetScale().y * 0.5f) > temp->GetPosition().y - (temp->GetScale().y * 0.5f))
			return true;

		return false;
	}
};