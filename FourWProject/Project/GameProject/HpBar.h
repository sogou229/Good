#pragma once
#include "Base/Base.h"

class HpBar : public Base
{
private:
    CImage m_img;

    int m_maxHp;
    int m_hp;

public:
    HpBar(bool isEnemy, int maxHp);

    void Update();
    void Draw();

    void Damage(int damage);

    int GetHp() const
    {
        return m_hp;
    }
};