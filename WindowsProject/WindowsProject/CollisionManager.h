#pragma once
#include "GameObject.h"

class CollisionManager
{
public:
	static bool CircleCollision(GameObject* temp, GameObject* dest)
	{
		float fx = dest->GetPosition().x - temp->GetPosition().x;
		float fy = dest->GetPosition().y - temp->GetPosition().y;

		float sum = (dest->GetScale().x + temp->GetScale().x) * 0.5f;

		float distance = sqrt((fx * fx) + (fx * fy));

		if (distance < sum)
			return true;

		return false;
	}
};