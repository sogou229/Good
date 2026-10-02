#include "HpBar.h"

HpBar::HpBar(bool isEnemy, int maxHp)
    : Base(eType_HpBar)
{
    m_maxHp = maxHp;
    m_hp = maxHp;
    m_isEnemy = isEnemy;

    m_img.SetCenter(0, 0);

    if (isEnemy)
    {
        // 敵HPバー
        m_img.Load("Image/EnemyHP.png");

        // 大きさを統一
        m_img.SetSize(650, 217);

        // 画面右上
        m_pos = CVector2D(1270, 25);
    }
    else
    {
        // プレイヤーHPバー
        m_img.Load("Image/PlayerHP.png");

        // 大きさを統一
        m_img.SetSize(650, 217);

        // 画面左上
        m_pos = CVector2D(20, 25);
    }

  
}


void HpBar::Update()
{
    float rate = (float)m_hp / (float)m_maxHp;

    float width = 650.0f * rate;

    m_img.SetSize(width, 217);
}


void HpBar::Draw()
{
    float rate = (float)m_hp / (float)m_maxHp;

    float maxWidth = 650.0f;
    float width = maxWidth * rate;

    m_img.SetSize(width, 217);

    if (m_isEnemy)
    {
        // 敵HPバー
        // 右端を固定して左側から減らす
        m_img.SetPos(CVector2D(1920.0f - 20.0f - width, 25.0f));
    }
    else
    {
        // プレイヤーHPバー
        // 左端を固定して右側から減らす
        m_img.SetPos(CVector2D(20.0f, 25.0f));
    }

    m_img.Draw();
}


void HpBar::Damage(int damage)
{
    m_hp -= damage;

    if (m_hp < 0)
    {
        m_hp = 0;
    }
    //HPの割合
    float rate = (float)m_hp / (float)m_maxHp;
    
    // HPバーの元の幅
    float maxWidth = 650.0f;

    // 現在の幅
    float width = maxWidth * rate;

    // HPバーの高さ
    float height = 217.0f;

    m_img.SetSize(width, height);

    if (m_isEnemy)
    {
        // 敵HPバーは右端を固定
        m_img.SetPos(CVector2D(1920.0f - 20.0f - width, 25.0f));
    }
    else
    {
        // プレイヤーHPバーは左端を固定
        m_img.SetPos(CVector2D(20.0f, 25.0f));
    }
}
