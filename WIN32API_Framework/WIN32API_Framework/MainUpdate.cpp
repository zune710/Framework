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
	
	m_pPlayer = new Player(); // GameObject ���� �� Player ����
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
		// GameObject�� �������� Player�� ��������(�޸� �����÷ο� ���� �߻��� �� ����. Ư�� Bullet)
		// Player(Bullet)�� �Ҹ��ڰ� ȣ���� �� �Ǿ��� ����
		// -> GameObject�� �Ҹ��ڿ� virtual �ٿ��� �ذ�
		delete m_pPlayer;
		m_pPlayer = NULL;
	}
}
