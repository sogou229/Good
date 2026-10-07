#pragma once
#include "Base/Base.h"

class EnemyAttack : public Base
{
private:
    int m_cnt;

public:
    EnemyAttack(const CVector2D& pos, bool flip);
    void Update();
    void Draw();
    void Collision(Base* b);
};