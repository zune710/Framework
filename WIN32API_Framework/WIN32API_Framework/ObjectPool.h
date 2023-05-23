#pragma once
#include "Include.h"

class GameObject;
class ObjectPool
{
public:
	Single(ObjectPool)

private:
	//list<GameObject*> PoolList;
	map<string, list<GameObject*>> PoolList;
public:
	//list<GameObject*>* GetList(string _key) { return &PoolList; }
	GameObject* GetPoolObject();
	void ReturnObject(GameObject* _Object);
private:
	ObjectPool();
public:
	~ObjectPool();
};

