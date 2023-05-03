#include "MainUpdate.h"
#include "Player.h"
#include "Enemy.h"

MainUpdate::MainUpdate() : m_pPlayer(NULL), m_pEnemy(NULL)
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

}

void MainUpdate::Update()
{
	if(m_pPlayer)
		m_pPlayer->Update();

	if(m_pEnemy)
		m_pEnemy->Update();
}

void MainUpdate::Render()
{
	Rectangle(m_hdc, 0, 0, WIDTH, HEIGHT);
	
	if (m_pPlayer)
		m_pPlayer->Render(m_hdc);

	if (m_pEnemy)
		m_pEnemy->Render(m_hdc);
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
