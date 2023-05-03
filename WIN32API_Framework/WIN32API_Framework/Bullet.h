#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	void Start()override;
	void Update()override;
	void Render(HDC hdc)override;
	void Destroy()override;
public:
	Bullet();
	virtual ~Bullet();  // �� �ᵵ virtual ��������� ������ ����
};

