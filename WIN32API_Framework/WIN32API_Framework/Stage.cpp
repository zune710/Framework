#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "ObjectManager.h"
#include "CollisionManager.h"
#include "Prototype.h"
#include "ObjectPool.h"

Stage::Stage() : m_pPlayer(nullptr), EnemyList(nullptr), BulletList(nullptr)
{
}

Stage::~Stage()
{
	Destroy();
}

void Stage::Start()
{
	GetSingle(Prototype)->Start();

	{
		GameObject* ProtoObj = GetSingle(Prototype)->GetGameObject("Player");  // 유니티 Prefab 과 비슷

		if (ProtoObj != nullptr)
		{
			m_pPlayer = ProtoObj->Clone();  // 유니티 Instantiate() 와 비슷
			m_pPlayer->Start();
		}
	}
	
	{
		GameObject* ProtoObj = GetSingle(Prototype)->GetGameObject("Enemy");
		
		if (ProtoObj != nullptr)
		{
			GameObject* Object = ProtoObj->Clone();
			GetSingle(ObjectManager)->AddObject(Object->Start());
		}
	}

	EnemyList = GetSingle(ObjectManager)->GetObjectList("Enemy");
}

int Stage::Update()
{
	if (m_pPlayer)
		m_pPlayer->Update();

	GetSingle(ObjectManager)->Update();
	
	/*
	if (EnemyList != nullptr && !EnemyList->empty())
		for (list<GameObject*>::iterator iter = EnemyList->begin(); iter != EnemyList->end(); ++iter)
			if(*iter != nullptr)
				(*iter)->Update();

	if (BulletList != nullptr && !BulletList->empty())
	{
		for (list<GameObject*>::iterator iter = BulletList->begin(); iter != BulletList->end(); ++iter)
			if (*iter != nullptr)
				if ((*iter)->Update())
				{
					(*iter)->Destroy();

					delete (*iter);
					(*iter) = nullptr;
				}
	}
	else
		BulletList = GetSingle(ObjectManager)->GetObjectList("Bullet");
	*/


	/*
	// Collision Check
	if (EnemyList != nullptr && !EnemyList->empty() && BulletList != nullptr && !BulletList->empty())
		for (list<GameObject*>::iterator enemyIter = EnemyList->begin(); enemyIter != EnemyList->end(); ++enemyIter)
			if(*enemyIter != nullptr)
			for (list<GameObject*>::iterator bulletIter = BulletList->begin(); bulletIter != BulletList->end(); ++bulletIter)
				if (*bulletIter != nullptr)
					if (CollisionManager::CircleCollision(*bulletIter, *enemyIter))
					{
						(*bulletIter)->Destroy();

						delete (*bulletIter);
						(*bulletIter) = nullptr;
					}
	*/

	return 0;
}

void Stage::Render(HDC hdc)
{
	if (m_pPlayer)
		m_pPlayer->Render(hdc);

	GetSingle(ObjectManager)->Render(hdc);


#ifdef DEBUG
	list<GameObject*>* enemyList = GetSingle(ObjectManager)->GetObjectList("Enemy");
	list<GameObject*>* normalList = GetSingle(ObjectManager)->GetObjectList("NormalBullet");
	list<GameObject*>* guideList = GetSingle(ObjectManager)->GetObjectList("GuideBullet");

	if (enemyList != nullptr && !enemyList->empty())
	{
		// ** Buffer 생성
		// ** 배열의 길이는 중요하지 않음 (충분하면 됨) - 어차피 지워질 것이기 때문
		char* EnemyBuffer = new char[128];  // 512, 1024 등

		// ** 정수를 문자열로 반환. 10진수로 변환됨.
		_itoa((int)enemyList->size(), EnemyBuffer, 10);

		// ** 문자열 포인터를 string으로 변환
		string str(EnemyBuffer);

		// ** 문자열 포인터 삭제 - str에 복사됐으니 이제 필요 없음
		delete[] EnemyBuffer;
		EnemyBuffer = nullptr;

		// ** 유니코드 형태로 생성
		wchar_t* t = new wchar_t[(int)str.size()];

		// ** 문자열 복사
		mbstowcs(t, str.c_str(), (int)str.size());

		// ** 출력
		TextOut(hdc, 50, 50, (LPCWSTR)t, (int)str.size());
	}

	if (normalList != nullptr && !normalList->empty())
	{
		char* NormalBuffer = new char[128];
		_itoa((int)normalList->size(), NormalBuffer, 10);

		string str(NormalBuffer);

		delete[] NormalBuffer;
		NormalBuffer = nullptr;

		wchar_t* t = new wchar_t[(int)str.size()];
		mbstowcs(t, str.c_str(), (int)str.size());

		TextOut(hdc, 50, 70, (LPCWSTR)t, (int)str.size());

		/* //문제 발생하는 방식
		char* NormalCount = new char[128];  // 이건 1바이트, TextOut 인자는 유니코드(2바이트) -> 글자 깨짐
		_itoa((int)normalList->size(), NormalCount, 10);
		TextOut(hdc, 50, 70, (LPCWSTR)NormalCount, strlen(NormalCount));
		*/
	}

	if (guideList != nullptr && !guideList->empty())
	{
		char* GuideBuffer = new char[128];
		_itoa((int)guideList->size(), GuideBuffer, 10);

		string str(GuideBuffer);

		delete[] GuideBuffer;
		GuideBuffer = nullptr;

		wchar_t* t = new wchar_t[(int)str.size()];
		mbstowcs(t, str.c_str(), (int)str.size());

		TextOut(hdc, 50, 90, (LPCWSTR)t, (int)str.size());
	}


	list<GameObject*>* NormalBulletList = GetSingle(ObjectPool)->GetList("NormalBullet");
	list<GameObject*>* GuideBulletList = GetSingle(ObjectPool)->GetList("GuideBullet");

	if (NormalBulletList != nullptr && !NormalBulletList->empty())
	{
		char* NormalBuffer = new char[128];
		_itoa((int)NormalBulletList->size(), NormalBuffer, 10);

		string str(NormalBuffer);

		delete[] NormalBuffer;
		NormalBuffer = nullptr;

		wchar_t* t = new wchar_t[(int)str.size()];
		mbstowcs(t, str.c_str(), (int)str.size());

		TextOut(hdc, 120, 50, (LPCWSTR)t, (int)str.size());
	}

	if (GuideBulletList != nullptr && !GuideBulletList->empty())
	{
		char* GuideBuffer = new char[128];
		_itoa((int)GuideBulletList->size(), GuideBuffer, 10);

		string str(GuideBuffer);

		delete[] GuideBuffer;
		GuideBuffer = nullptr;

		wchar_t* t = new wchar_t[(int)str.size()];
		mbstowcs(t, str.c_str(), (int)str.size());

		TextOut(hdc, 120, 70, (LPCWSTR)t, (int)str.size());
	}
#endif  // DEBUG


	/*
	if (EnemyList != nullptr && !EnemyList->empty())
		for (list<GameObject*>::iterator iter = EnemyList->begin(); iter != EnemyList->end(); ++iter)
			if (*iter != nullptr)
				(*iter)->Render(hdc);

	if (BulletList != nullptr && !BulletList->empty())
		for (list<GameObject*>::iterator iter = BulletList->begin(); iter != BulletList->end(); ++iter)
			if (*iter != nullptr)
				(*iter)->Render(hdc);
	*/
}

void Stage::Destroy()
{
	if (m_pPlayer)
	{
		delete m_pPlayer;
		m_pPlayer = NULL;
	}

	if (EnemyList != nullptr && !EnemyList->empty())
	{
		for (list<GameObject*>::iterator iter = EnemyList->begin(); iter != EnemyList->end(); ++iter)
		{
			delete (*iter);
			(*iter) = nullptr;
		}
		EnemyList->clear();
	}

	if (BulletList != nullptr && !BulletList->empty())
	{
		for (list<GameObject*>::iterator iter = BulletList->begin(); iter != BulletList->end(); ++iter)
		{
			delete (*iter);
			(*iter) = nullptr;
		}
		BulletList->clear();
	}
}
