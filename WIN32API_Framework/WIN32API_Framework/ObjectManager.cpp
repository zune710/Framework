#include "ObjectManager.h"
#include "GameObject.h"

ObjectManager* ObjectManager::Instance = nullptr;

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{

}

void ObjectManager::AddObject(GameObject* _Object)
{
	map<string, list<GameObject*>>::iterator iter = ObjectList.find(_Object->GetKey());

	if (iter == ObjectList.end())
	{
		list<GameObject*> tempList;
		tempList.push_back(_Object);

		ObjectList.insert(make_pair(_Object->GetKey(), tempList));
	}
	else
		iter->second.push_back(_Object);

	// iter->first: key
	// iter->second: value
}


list<GameObject*>* ObjectManager::GetObjectList(string key)  // ���ڿ��� &: ���۷���
{
	map<string, list<GameObject*>>::iterator iter = ObjectList.find(key);
	
	if (iter == ObjectList.end())
		return nullptr;
	else
		return &iter->second;  // &: �ּ� ��ȯ ������
}

