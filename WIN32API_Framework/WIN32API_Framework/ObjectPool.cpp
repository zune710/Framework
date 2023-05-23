#include "ObjectPool.h"

ObjectPool::ObjectPool()
{
}

ObjectPool::~ObjectPool()
{
}

GameObject* ObjectPool::GetPoolObject()
{
	//test
	GameObject* Obj = *(PoolList.begin());
	PoolList.pop_front();
	return Obj;
}

void ObjectPool::ReturnObject(GameObject* _Object)
{
	PoolList.push_back(_Object);
}
