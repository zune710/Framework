#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "ObjectManager.h"
#include "CollisionManager.h"

Stage::Stage() : m_pPlayer(nullptr), EnemyList(nullptr), BulletList(nullptr)
{
}

Stage::~Stage()
{
	Destroy();
}

void Stage::Start()
{
	m_pPlayer = (new Player)->Start();

	GetSingle(ObjectManager).AddObject(
		(new Enemy)->Start());
	/*ObjectManager::GetInstance()->AddObject(
		(new Enemy)->Start());*/

	EnemyList = GetSingle(ObjectManager).GetObjectList("Enemy");
	//EnemyList = ObjectManager::GetInstance()->GetObjectList("Enemy");
}

int Stage::Update()
{
	if (m_pPlayer)
		m_pPlayer->Update();

	if (EnemyList != nullptr && !EnemyList->empty())
		for (list<GameObject*>::iterator iter = EnemyList->begin(); iter != EnemyList->end(); ++iter)
			if(*iter != nullptr)
				(*iter)->Update();

	if (BulletList != nullptr && !BulletList->empty())
		for (list<GameObject*>::iterator iter = BulletList->begin(); iter != BulletList->end(); ++iter)
			if (*iter != nullptr)
				if ((*iter)->Update())
				{
					delete (*iter);
					(*iter) = nullptr;
				}
	else
		BulletList = GetSingle(ObjectManager).GetObjectList("Bullet");
		//BulletList = ObjectManager::GetInstance()->GetObjectList("Bullet");


	// collision
	if (EnemyList != nullptr && !EnemyList->empty() && BulletList != nullptr && !BulletList->empty())
		for (list<GameObject*>::iterator enemyIter = EnemyList->begin(); enemyIter != EnemyList->end(); ++enemyIter)
			for (list<GameObject*>::iterator bulletIter = BulletList->begin(); bulletIter != BulletList->end(); ++bulletIter)
				if (*enemyIter != nullptr && *bulletIter != nullptr)
					if (CollisionManager::CircleCollision(*bulletIter, *enemyIter))
					{
						delete (*bulletIter);
						(*bulletIter) = nullptr;
					}

	return 0;
}

void Stage::Render(HDC hdc)
{
	if (m_pPlayer)
		m_pPlayer->Render(hdc);

	if (EnemyList != nullptr && !EnemyList->empty())
		for (list<GameObject*>::iterator iter = EnemyList->begin(); iter != EnemyList->end(); ++iter)
			if (*iter != nullptr)
				(*iter)->Render(hdc);

	if (BulletList != nullptr && !BulletList->empty())
		for (list<GameObject*>::iterator iter = BulletList->begin(); iter != BulletList->end(); ++iter)
			if (*iter != nullptr)
				(*iter)->Render(hdc);
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
