#include "MainUpdate.h"
#include "Player.h"

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
	
	m_pPlayer = new Player(); // GameObject 생성 후 Player 생성
	m_pPlayer->Start();
}

void MainUpdate::Update()
{
	if(m_pPlayer)
		m_pPlayer->Update();
}

void MainUpdate::Render()
{
	Rectangle(m_hdc, 0, 0, 1420, 720);
	
	if (m_pPlayer)
		m_pPlayer->Render(m_hdc);
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
}
