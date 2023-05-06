#include "Stage.h"
#include "Player.h"
#include "Enemy.h"

Stage::Stage()
{
}

Stage::~Stage()
{
}

void Stage::Start()
{
    m_pPlayer = new Player();
    m_pPlayer->Start();

    m_pEnemy = new Enemy();
    m_pEnemy->Start();
}

int Stage::Update()
{
    if (m_pPlayer)
        m_pPlayer->Update();

    if (m_pEnemy)
        m_pEnemy->Update();

    return 0;
}

void Stage::Render(HDC hdc)
{
    if (m_pPlayer)
        m_pPlayer->Render(hdc);

    if (m_pEnemy)
        m_pEnemy->Render(hdc);
}

void Stage::Destroy()
{
    if (m_pPlayer)
    {
        delete m_pPlayer;
        m_pPlayer = NULL;
    }

    if (m_pEnemy)
    {
        delete m_pEnemy;
        m_pEnemy = NULL;
    }
}
