#include "ObjectManager.h"
#include "GameObject.h"
#include "CollisionManager.h"

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{

}

void ObjectManager::AddObject(GameObject* _Object)
{
	// ** 파라미터가 가리키고 있는 키 값이 현재 map에 포함되어 있는지 확인
	map<string, list<GameObject*>>::iterator iter = ObjectList.find(_Object->GetKey());

	// ** 만약 키가 없다면...
	if (iter == ObjectList.end())
	{
		// ** map에 포함시킬 list를 생성한 후...
		list<GameObject*> tempList;

		// ** 리스트에 오브젝트를 추가
		tempList.push_back(_Object);

		// ** 오브젝트가 추가된 리스트를 map에 추가
		ObjectList.insert(make_pair(_Object->GetKey(), tempList));
	}
	// ** 이미 키가 존재한다면...
	else
		// ** 해당 리스트에 오브젝트를 추가
		iter->second.push_back(_Object);
}


list<GameObject*>* ObjectManager::GetObjectList(const string& key)
{
	// ** 키 값이 현재 map에 포함되어 있는지 확인
	map<string, list<GameObject*>>::iterator iter = ObjectList.find(key);

	// ** 만약 키가 없다면...
	if (iter == ObjectList.end())
		// ** nullptr 을 반환
		return nullptr;
	// ** 이미 키가 존재한다면...
	else
		// ** second = value = list<GameObject*> 를 반환
		return &iter->second;
}

void ObjectManager::Update()
{
	for (map<string, list<GameObject*>>::iterator iter = ObjectList.begin();
		iter != ObjectList.end(); ++iter)
	{
		for (list<GameObject*>::iterator iter2 = iter->second.begin();
			iter2 != iter->second.end();)
		{
			int result = (*iter2)->Update();

			if (result == 1)
			{
				(*iter2)->Destroy();
				iter2 = iter->second.erase(iter2);
			}
			else
				++iter2;
		}
	}

	CollisionCheck();

}

void ObjectManager::Render(HDC _hdc)
{
	for (map<string, list<GameObject*>>::iterator iter = ObjectList.begin();
		iter != ObjectList.end(); ++iter)
		for (list<GameObject*>::iterator iter2 = iter->second.begin();
			iter2 != iter->second.end(); ++iter2)
			(*iter2)->Render(_hdc);
}


void ObjectManager::CollisionCheck()
{
	list<GameObject*>* EnemyList = &ObjectList["Enemy"];
	list<GameObject*>* NormalList = &ObjectList["NormalBullet"];
	list<GameObject*>* GuideList = &ObjectList["GuideBullet"];

	for (list<GameObject*>::iterator iter = EnemyList->begin();
		iter != EnemyList->end(); ++iter)
	{
		for (list<GameObject*>::iterator iter2 = NormalList->begin();
			iter2 != NormalList->end();)
		{
			if (CollisionManager::CircleCollision(*iter2, *iter))
			{
				(*iter2)->Destroy();

				iter2 = NormalList->erase(iter2);
			}
			else
				++iter2;
		}

		for (list<GameObject*>::iterator iter2 = GuideList->begin();
			iter2 != GuideList->end();)
		{
			if (CollisionManager::CircleCollision(*iter2, *iter))
			{
				(*iter2)->Destroy();

				iter2 = GuideList->erase(iter2);
			}
			else
				++iter2;
		}
	}
}
