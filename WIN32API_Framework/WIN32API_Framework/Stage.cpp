#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "ObjectManager.h"
#include "CollisionManager.h"

Stage::Stage() : m_pPlayer(nullptr)
{
}

Stage::~Stage()
{
}

void Stage::Start()
{
	m_pPlayer = new Player(); // GameObject 持失 板 Player 持失
	m_pPlayer->Start();

	ObjectManager::GetInstance()->AddObject((new Enemy())->Start());
}

int Stage::Update()
{
	if (m_pPlayer)
		m_pPlayer->Update();

	list<GameObject*>* EnemyList = ObjectManager::GetInstance()->GetObjectList("Enemy");
	list<GameObject*>* BulletList = ObjectManager::GetInstance()->GetObjectList("Bullet");

	if (EnemyList != nullptr && !EnemyList->empty())
	{
		for (list<GameObject*>::iterator iter = EnemyList->begin(); iter != EnemyList->end(); ++iter)
			if(*iter != nullptr)
				(*iter)->Update();
	}

	if (BulletList != nullptr && !BulletList->empty())
	{
		for (list<GameObject*>::iterator iter = BulletList->begin(); iter != BulletList->end(); ++iter)
		{
			if (*iter != nullptr)
			{
				if ((*iter)->Update())
				{
					delete* iter;
					*iter = nullptr;
				}
			}
		}
	}

	if (EnemyList != nullptr && !EnemyList->empty() && BulletList != nullptr && !BulletList->empty())
	{
		for (list<GameObject*>::iterator enemyIter = EnemyList->begin(); enemyIter != EnemyList->end(); ++enemyIter)
		{
			for (list<GameObject*>::iterator bulletIter = BulletList->begin(); bulletIter != BulletList->end(); ++bulletIter)
			{
				if (*enemyIter != nullptr && *bulletIter != nullptr)
				{
					if (CollisionManager::CircleCollision(*enemyIter, *bulletIter))
					{
						delete* bulletIter;
						*bulletIter = nullptr;
					}
				}
			}
		}
	}

	return 0;
}

void Stage::Render(HDC hdc)
{
	if (m_pPlayer)
		m_pPlayer->Render(hdc);

	list<GameObject*>* EnemyList = ObjectManager::GetInstance()->GetObjectList("Enemy");
	list<GameObject*>* BulletList = ObjectManager::GetInstance()->GetObjectList("Bullet");

	if (EnemyList != nullptr && !EnemyList->empty())
	{
		for (list<GameObject*>::iterator iter = EnemyList->begin(); iter != EnemyList->end(); ++iter)
			if (*iter != nullptr)
				(*iter)->Render(hdc);
	}

	if (BulletList != nullptr && !BulletList->empty())
	{
		for (list<GameObject*>::iterator iter = BulletList->begin(); iter != BulletList->end(); ++iter)
			if (*iter != nullptr)
				(*iter)->Render(hdc);
	}
}

void Stage::Destroy()
{
	if (m_pPlayer)
	{
		delete m_pPlayer;
		m_pPlayer = NULL;
	}

	/*if (m_pEnemy)
	{
		delete m_pEnemy;
		m_pEnemy = NULL;
	}*/
}
