#pragma once
#include "Base/Base.h"

class PlayerAttack : public Base
{
private:
    int m_cnt;
public:
    PlayerAttack(const CVector2D& pos, bool flip);

    void Update();
    void Draw();
    void Collision(Base* b);
};