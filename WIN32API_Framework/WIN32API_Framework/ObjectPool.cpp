#include "ObjectPool.h"
#include "GameObject.h"

ObjectPool::ObjectPool()
{
}

ObjectPool::~ObjectPool()
{
}

void ObjectPool::ReturnObject(GameObject* _Object)
{
	map<string, list<GameObject*>>::iterator iter = PoolList.find(_Object->GetKey());

	if (iter == PoolList.end())
	{
		list<GameObject*> tempList;
		tempList.push_back(_Object);
		PoolList.insert(make_pair(_Object->GetKey(), tempList));
	}
	else
		iter->second.push_back(_Object);
}
