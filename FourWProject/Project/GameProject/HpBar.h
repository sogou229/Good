#pragma once
#include "Base/Base.h"

class HpBar : public Base
{
private:
    CImage m_img;

    int m_maxHp;
    int m_hp;

    bool m_isEnemy;

public:
    HpBar(bool isEnemy, int maxHp);

    void Update();
    void Draw();

    void Damage(int damage);

    void SetUp(int hp);

    int GetHp() const
    {
        return m_hp;
    }
    int GetMaxHp()const {
        return m_maxHp;
    }
};