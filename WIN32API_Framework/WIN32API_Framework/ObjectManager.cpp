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
	// ** �Ķ���Ͱ� ����Ű�� �ִ� Ű ���� ���� map�� ���ԵǾ� �ִ��� Ȯ��
	map<string, list<GameObject*>>::iterator iter = ObjectList.find(_Object->GetKey());

	// ** ���� Ű�� ���ٸ�...
	if (iter == ObjectList.end())
	{
		// ** map�� ���Խ�ų list�� ������ ��...
		list<GameObject*> tempList;

		// ** ����Ʈ�� ������Ʈ�� �߰�
		tempList.push_back(_Object);

		// ** ������Ʈ�� �߰��� ����Ʈ�� map�� �߰�
		ObjectList.insert(make_pair(_Object->GetKey(), tempList));
	}
	// ** �̹� Ű�� �����Ѵٸ�...
	else
		// ** �ش� ����Ʈ�� ������Ʈ�� �߰�
		iter->second.push_back(_Object);
}


list<GameObject*>* ObjectManager::GetObjectList(const string& key)
{
	// ** Ű ���� ���� map�� ���ԵǾ� �ִ��� Ȯ��
	map<string, list<GameObject*>>::iterator iter = ObjectList.find(key);

	// ** ���� Ű�� ���ٸ�...
	if (iter == ObjectList.end())
		// ** nullptr �� ��ȯ
		return nullptr;
	// ** �̹� Ű�� �����Ѵٸ�...
	else
		// ** second = value = list<GameObject*> �� ��ȯ
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
