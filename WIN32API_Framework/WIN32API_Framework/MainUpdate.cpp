#include "MainUpdate.h"
#include "Player.h"
#include "Enemy.h"
#include "ObjectManager.h"
#include "CollisionManager.h"

MainUpdate::MainUpdate() : m_pPlayer(NULL)
{

}

MainUpdate::~MainUpdate()
{
	Destroy();
}

void MainUpdate::Start()
{
	m_hdc = GetDC(g_hWnd);
	
	m_pPlayer = new Player(); // GameObject ���� �� Player ����
	m_pPlayer->Start();

	m_pEnemy = new Enemy();
	m_pEnemy->Start();

	ObjectManager::GetInstance()->AddObject(m_pEnemy);
}

void MainUpdate::Update()
{
	//list<GameObject*>* EnemyList = ObjectManager::GetInstance()->GetObjectList("Enemy");
	//list<GameObject*>* BulletList = ObjectManager::GetInstance()->GetObjectList("Bullet");
	
	if(m_pPlayer)
		m_pPlayer->Update();

	/*if (EnemyList != nullptr && !EnemyList->empty())
	{
		for (list<GameObject*>::iterator iter = EnemyList->begin(); iter != EnemyList->end(); ++iter)
			(*iter)->Update();
	}

	if (BulletList != nullptr && !BulletList->empty())
	{
		for (list<GameObject*>::iterator iter = BulletList->begin(); iter != BulletList->end(); ++iter)
		{
			if ((*iter)->Update())
			{
				delete* iter;
				*iter = nullptr;
			}
		}
	}

	if (EnemyList != nullptr && !EnemyList->empty() && BulletList != nullptr && !BulletList->empty())
	{
		for (list<GameObject*>::iterator enemyIter = EnemyList->begin(); enemyIter != EnemyList->end(); ++enemyIter)
		{
			for (list<GameObject*>::iterator bulletIter = BulletList->begin(); bulletIter != BulletList->end(); ++bulletIter)
			{
				if (CollisionManager::CircleCollision(*enemyIter, *bulletIter))
				{
					delete* bulletIter;
					*bulletIter = nullptr;
				}
			}
		}
	}*/
}

void MainUpdate::Render()
{
	list<GameObject*>* EnemyList = ObjectManager::GetInstance()->GetObjectList("Enemy");
	list<GameObject*>* BulletList = ObjectManager::GetInstance()->GetObjectList("Bullet");
	
	Rectangle(m_hdc, 0, 0, WIDTH, HEIGHT);
	
	if (m_pPlayer)
		m_pPlayer->Render(m_hdc);

	if (EnemyList != nullptr && !EnemyList->empty())
	{
		for (list<GameObject*>::iterator iter = EnemyList->begin(); iter != EnemyList->end(); ++iter)
			(*iter)->Render(m_hdc);
	}
	
	if (BulletList != nullptr && !BulletList->empty())
	{
		for (list<GameObject*>::iterator iter = BulletList->begin(); iter != BulletList->end(); ++iter)
			(*iter)->Render(m_hdc);
	}
}

void MainUpdate::Destroy()
{
	if (m_pPlayer)
	{
		// GameObject�� �������� Player�� ��������(�޸� �����÷ο� ���� �߻��� �� ����. Ư�� Bullet)
		// Player(Bullet)�� �Ҹ��ڰ� ȣ���� �� �Ǿ��� ����
		// -> GameObject�� �Ҹ��ڿ� virtual �ٿ��� �ذ�
		delete m_pPlayer;
		m_pPlayer = NULL;
	}

	if (m_pEnemy)
	{
		delete m_pEnemy;
		m_pEnemy = NULL;
	}
}
