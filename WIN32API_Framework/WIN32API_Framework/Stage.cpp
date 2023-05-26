#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "ObjectManager.h"
#include "CollisionManager.h"
#include "Prototype.h"
#include "ObjectPool.h"
#include "ImageManager.h"
#include "Bitmap.h"

Stage::Stage() : m_pPlayer(nullptr), EnemyList(nullptr), BulletList(nullptr), m_mapImageList(nullptr)
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
		GameObject* ProtoObj = GetSingle(Prototype)->GetGameObject("Player");

		if (ProtoObj != nullptr)
		{
			m_pPlayer = ProtoObj->Clone();
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

	m_mapImageList = GetSingle(ImageManager)->GetImageList();

	(*m_mapImageList)["BackGround"] = (new Bitmap)->LoadBmp(L"../Resource/Stage/BackGround.bmp");
	(*m_mapImageList)["Buffer"] = (new Bitmap)->LoadBmp(L"../Resource/Stage/Buffer.bmp");

	/*
	m_mapImageList->insert(
		make_pair("BackGround", (new Bitmap)->LoadBmp(L"../Resource/Stage/BackGround.bmp")));  // .. : 뒤로가기
	m_mapImageList->insert(
		make_pair("Buffer", (new Bitmap)->LoadBmp(L"../Resource/Stage/Buffer.bmp")));
	*/
	
	GameObject::SetImageList(m_mapImageList);
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
	BitBlt((*m_mapImageList)["Buffer"]->GetMemDC(),   // 복사해 넣을 그림판 ?!
		0, 0, WIDTH, HEIGHT,                          // 복사할 영역 시작점으로부터 끝부분까지
		(*m_mapImageList)["BackGround"]->GetMemDC(),  // 복사할 이미지
		0, 0,                                         // 스케일을 잡아준다.
		SRCCOPY);                                     // 소스 영역을 대상 영역에 복사한다.
	// -> 1. Buffer 그림판에 BackGround 그리기

	if (m_pPlayer)
		m_pPlayer->Render(
			(*m_mapImageList)["Buffer"]->GetMemDC());
	// -> 2. Buffer 그림판에 Player 그리기

	GetSingle(ObjectManager)->Render(
		(*m_mapImageList)["Buffer"]->GetMemDC());
	// -> 3. Buffer 그림판에 오브젝트들(Bullet, Enemy) 그리기

	BitBlt(hdc,                                       // 복사해 넣을 그림판 ?!
		0, 0, WIDTH, HEIGHT,                          // 복사할 영역 시작점으로부터 끝부분까지
		(*m_mapImageList)["Buffer"]->GetMemDC(),      // 복사할 이미지
		0, 0,                                         // 스케일을 잡아준다.
		SRCCOPY);                                     // 소스 영역을 대상 영역에 복사한다.
	// -> 4. 다 그려진 Buffer를 hdc로 그려서 화면에 출력
	// -> 1 ~ 4: 이렇게 하면 파이팅 현상 안 생겨서 깜빡이지 않음


#ifdef DEBUG
	TextOut(hdc, 70, 30, L"Manager", (int)strlen("Manager"));
	TextOut(hdc, 140, 30, L"Pool", (int)strlen("Pool"));
	TextOut(hdc, 10, 50, L"Enemy", (int)strlen("Enemy"));
	TextOut(hdc, 10, 70, L"Normal", (int)strlen("Normal"));
	TextOut(hdc, 10, 90, L"Guide", (int)strlen("Guide"));


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
