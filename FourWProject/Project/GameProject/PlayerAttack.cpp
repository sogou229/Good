#include "PlayerAttack.h"
#include "Enemy.h"

PlayerAttack::PlayerAttack(const CVector2D& pos, bool flip)
    : Base(eType_Player_Attack)
    ,m_cnt(0)
{
    m_pos = pos;

    if (flip)
    {
        m_pos.x -= 150;
    }
    else
    {
        m_pos.x += 150;
    }

    // UŒ‚”»’è
    m_rect = CRect(-100,0,100,100);
}

void PlayerAttack::Update()
{
    m_cnt++;

    if (m_cnt >= 10)
    {
        SetKill();
    }
}

void PlayerAttack::Draw()
{
    DrawRect();
}

void PlayerAttack::Collision(Base* b)
{
    if (b->GetType() == eType_Enemy)
    {
        if (CollisionRect(this, b))
        {
            printf("HIT!\n");

            Enemy* enemy = (Enemy*)b;
            enemy->Damage(10);

            SetKill();
        }
    }
}