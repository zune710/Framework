#pragma once
#include "Include.h"

class GameObject;
class ObjectManager
{
public:
	Single(ObjectManager)

private:
	map<string, list<GameObject*>> ObjectList; // ���Ǵ� ������Ʈ�鸸 ����
public:
	void AddObject(GameObject* _Object);

	list<GameObject*>* GetObjectList(const string& key);
	void Update();
	void Render(HDC _hdc);
private:
	ObjectManager();
public:
	~ObjectManager();
};
