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
	
	m_pPlayer = new Player(); // GameObject 생성 후 Player 생성
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
		// GameObject만 지워지고 Player는 남아있음(메모리 오버플로우 문제 발생할 수 있음. 특히 Bullet)
		// Player(Bullet)의 소멸자가 호출이 안 되었기 때문
		// -> GameObject의 소멸자에 virtual 붙여서 해결
		delete m_pPlayer;
		m_pPlayer = NULL;
	}

	if (m_pEnemy)
	{
		delete m_pEnemy;
		m_pEnemy = NULL;
	}
}
