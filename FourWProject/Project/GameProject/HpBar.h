#pragma once
#include "Base/Base.h"

class HpBar : public Base
{
private:
    CImage m_img;

    int m_maxHp;
    int m_hp;

    bool m_isEnemy;

    static HpBar* s_playerBar;
    static HpBar* s_enemyBar;
public:
    HpBar(bool isEnemy, int maxHp);
  
    void Damage(int damage);
    void SetHp(int hp);

    static HpBar* GetBar(bool isEnemy);

    void Update();
    void Draw();

    void DrawGauge(float width, float height);
    int GetHp() const
    {
        return m_hp;
    }

    int GetMaxHp()const {
        return m_maxHp;
    }
};