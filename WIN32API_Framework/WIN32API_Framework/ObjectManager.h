#pragma once
#include "Include.h"

class GameObject;
class ObjectManager
{
public:
	Single(ObjectManager)

private:
	map<string, list<GameObject*>> ObjectList;
public:
	void AddObject(GameObject* _Object);

	list<GameObject*>* GetObjectList(const string& key);
	void Update();
	void Render(HDC _hdc);
	void CollisionCheck();
private:
	ObjectManager();
public:
	~ObjectManager();
};

