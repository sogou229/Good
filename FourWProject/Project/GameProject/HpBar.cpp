#include "HpBar.h"

HpBar::HpBar(bool isEnemy, int maxHp)
    : Base(eType_HpBar)
{
    m_maxHp = maxHp;
    m_hp = maxHp;

    if (isEnemy)
    {
        // 敵HPバー
        m_img.Load("Image/EnemyHP.png");

        // 大きさを統一
        m_img.SetSize(650, 217);

        // 画面右上
        m_pos = CVector2D(1200, 100);
    }
    else
    {
        // プレイヤーHPバー
        m_img.Load("Image/PlayerHP.png");

        // 大きさを統一
        m_img.SetSize(650, 217);

        // 画面左上
        m_pos = CVector2D(20, 100);
    }

    // 左上を基準
    m_img.SetCenter(0, 0);
}


void HpBar::Update()
{
}


void HpBar::Draw()
{
    // HPバーは画面固定UIなので
    // GetScreenPos()を使わない
    m_img.SetPos(m_pos);

    m_img.Draw();
}


void HpBar::Damage(int damage)
{
    m_hp -= damage;

    if (m_hp < 0)
    {
        m_hp = 0;
    }
}