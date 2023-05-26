#pragma once
#include "GameObject.h"

class CollisionManager
{
public:
	// ** ��(���׶��) �浹
	static bool CircleCollision(GameObject* temp, GameObject* dest)  //temp = current, dest = target
	{
		// ** x���� y���� ���Ѵ�.
		float fx = dest->GetPosition().x - temp->GetPosition().x;  // ���⼺�� ���´�.(dest�� ���� ����)
		float fy = dest->GetPosition().y - temp->GetPosition().y;

		// ** ������ ���� �������� ���� ���Ѵ�.
		float sum = (dest->GetScale().x + temp->GetScale().x) * 0.5f;


		// ** �Ÿ��� ���Ѵ�.
		float value = (fx * fx) + (fy * fy);
		float distance = (float)sqrt((double)value);

		// ** �Ÿ��� �������� �պ��� �۴ٸ� �浹
		if (distance < sum)
			return true;

		return false;
	}

	// ** Rect �浹
	static bool RectCollision(GameObject* temp, GameObject* dest)
	{
		// ** ������ Rect ��, ��, ��, �� ��ǥ�� ���Ͽ� �浹�� Ȯ��
		if (temp->GetPosition().x + (temp->GetScale().x * 0.5f) > dest->GetPosition().x - (dest->GetScale().x * 0.5f) &&
			dest->GetPosition().x + (dest->GetScale().x * 0.5f) > temp->GetPosition().x - (temp->GetScale().x * 0.5f) &&
			temp->GetPosition().y + (temp->GetScale().y * 0.5f) > dest->GetPosition().y - (dest->GetScale().y * 0.5f) &&
			dest->GetPosition().y + (dest->GetScale().y * 0.5f) > temp->GetPosition().y - (temp->GetScale().y * 0.5f))
			return true;

		return false;
	}
};