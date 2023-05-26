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
		GameObject* ProtoObj = GetSingle(Prototype)->GetGameObject("Player");  // ����Ƽ Prefab �� ���

		if (ProtoObj != nullptr)
		{
			m_pPlayer = ProtoObj->Clone();  // ����Ƽ Instantiate() �� ���
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
	
	




	// Collision Check
	list<GameObject*>* NormalList = GetSingle(ObjectManager)->GetObjectList("NormalBullet");
	list<GameObject*>* GuideList = GetSingle(ObjectManager)->GetObjectList("GuideBullet");

	if (EnemyList != nullptr && !EnemyList->empty() && NormalList != nullptr && !NormalList->empty())
		for (list<GameObject*>::iterator iter = EnemyList->begin(); iter != EnemyList->end(); ++iter)
			for (list<GameObject*>::iterator iter2 = NormalList->begin(); iter2 != NormalList->end();)
			{
				if (CollisionManager::CircleCollision(*iter2, *iter))
				{
					(*iter2)->Destroy();

					iter2 = NormalList->erase(iter2);
				}
				else
					++iter2;
			}

	if (EnemyList != nullptr && !EnemyList->empty() && GuideList != nullptr && !GuideList->empty())
		for (list<GameObject*>::iterator iter = EnemyList->begin(); iter != EnemyList->end(); ++iter)
			for (list<GameObject*>::iterator iter2 = GuideList->begin(); iter2 != GuideList->end();)
			{
				if (CollisionManager::CircleCollision(*iter2, *iter))
				{
					(*iter2)->Destroy();

					iter2 = GuideList->erase(iter2);
				}
				else
					++iter2;
			}

	return 0;
}

void Stage::Render(HDC hdc)
{
	if (m_pPlayer)
		m_pPlayer->Render(hdc);

	GetSingle(ObjectManager)->Render(hdc);


#ifdef DEBUG
	TextOut(hdc, 70, 30, L"Manager", strlen("Manager"));
	TextOut(hdc, 140, 30, L"Pool", strlen("Pool"));
	TextOut(hdc, 10, 50, L"Enemy", strlen("Enemy"));
	TextOut(hdc, 10, 70, L"Normal", strlen("Normal"));
	TextOut(hdc, 10, 90, L"Guide", strlen("Guide"));


	list<GameObject*>* enemyList = GetSingle(ObjectManager)->GetObjectList("Enemy");
	list<GameObject*>* normalList = GetSingle(ObjectManager)->GetObjectList("NormalBullet");
	list<GameObject*>* guideList = GetSingle(ObjectManager)->GetObjectList("GuideBullet");

	if (enemyList != nullptr && !enemyList->empty())
	{
		// ** Buffer ����
		// ** �迭�� ���̴� �߿����� ���� (����ϸ� ��) - ������ ������ ���̱� ����
		char* EnemyBuffer = new char[128];  // 512, 1024 ��

		// ** ������ ���ڿ��� ��ȯ. 10������ ��ȯ��.
		_itoa((int)enemyList->size(), EnemyBuffer, 10);

		// ** ���ڿ� �����͸� string���� ��ȯ
		string str(EnemyBuffer);

		// ** ���ڿ� ������ ���� - str�� ��������� ���� �ʿ� ����
		delete[] EnemyBuffer;
		EnemyBuffer = nullptr;

		// ** �����ڵ� ���·� ����
		wchar_t* t = new wchar_t[(int)str.size()];

		// ** ���ڿ� ����
		mbstowcs(t, str.c_str(), (int)str.size());

		// ** ���
		TextOut(hdc, 70, 50, (LPCWSTR)t, (int)str.size());
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

		TextOut(hdc, 70, 70, (LPCWSTR)t, (int)str.size());

		/* //���� �߻��ϴ� ���
		char* NormalCount = new char[128];  // �̰� 1����Ʈ, TextOut ���ڴ� �����ڵ�(2����Ʈ) -> ���� ����
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

		TextOut(hdc, 70, 90, (LPCWSTR)t, (int)str.size());
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

		TextOut(hdc, 140, 70, (LPCWSTR)t, (int)str.size());
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

		TextOut(hdc, 140, 90, (LPCWSTR)t, (int)str.size());
	}
#endif  // DEBUG
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
