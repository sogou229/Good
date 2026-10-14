#include "EnemyAttack.h"
#include "Player.h"

EnemyAttack::EnemyAttack(const CVector2D& pos, bool flip)
    : Base(eType_Enemy_Attack)
    , m_cnt(0)
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

    m_rect = CRect(-100, -100, 100, 0);
}

void EnemyAttack::Update()
{
    m_cnt++;

    if (m_cnt >= 10)
    {
        SetKill();
    }
}

void EnemyAttack::Draw()
{
    DrawRect();
}

void EnemyAttack::Collision(Base* b)
{
    if (b->GetType() == eType_Player)
    {
        if (CollisionRect(this, b))
        {
            Player* player = static_cast<Player*>(b);
            player->Damage(10);
            printf("PLAYER HIT!!\n");

           // Player* player = (Player*)b;
            player->Damage(10);

            SetKill();
        }
    }
}