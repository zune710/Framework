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
	// ** 파라메터가 가리키고 있는 키 값이 현재 map에 포함되어 있는지 확인
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

	// iter->first: key
	// iter->second: value
}


list<GameObject*>* ObjectManager::GetObjectList(const string& key)  //  레퍼런스 연산자 사용하면 값이 변할 수 있으므로 const 붙여줌
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
		return &iter->second;  // &: 주소 반환 연산자(레퍼런스 연산자)
}

