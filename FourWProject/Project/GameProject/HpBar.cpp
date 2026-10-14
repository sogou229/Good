#include "HpBar.h"

HpBar* HpBar::s_playerBar = nullptr;
HpBar* HpBar::s_enemyBar = nullptr;

HpBar::HpBar(bool isEnemy, int maxHp)
    : Base(eType_HpBar)
{
    m_maxHp = maxHp;
    m_hp = maxHp;
    m_isEnemy = isEnemy;

    if (m_isEnemy)
    {
        s_enemyBar = this;
    }
    else
    {
        s_playerBar = this;
    }

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
    //Hpの割合
    float rate = (float)m_hp / (float)m_maxHp;
    // HPバー全体のサイズ
    float maxWidth = 650.0f;
    float height = 217.0f;

    // 枠・背景の画像は縮めずに描画
    m_img.SetSize(maxWidth, height);

    if (m_isEnemy)
    {
        m_img.SetPos(CVector2D(1270, 25));
    }
    else
    {
        m_img.SetPos(CVector2D(20, 25));
    }

    m_img.Draw();

    // 緑色のゲージの幅
    float gaugeWidth = maxWidth * rate;

    // ゲージの位置
    float gaugeX;
    if (m_isEnemy)
    {
        // 敵：右側を固定して左方向に減らす
        gaugeX = 1920.0f - 20.0f - gaugeWidth;
    }
    else
    {
        // プレイヤー：左側を固定して右方向に減らす
        gaugeX = 20.0f;
    }

    // 緑色のゲージを描画
    Utility::DrawQuad(
        CVector2D(gaugeX, 25.0f),
        CVector2D(gaugeWidth, height),
        CVector4D(0, 1, 0, 1)
    );
}


void HpBar::Damage(int hp)
{
    m_hp -= hp;

    if (m_hp < 0)
        m_hp = 0;

    if (m_hp > m_maxHp)
        m_hp = m_maxHp;
    
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
HpBar* HpBar::GetBar(bool isEnemy)
{
    if (isEnemy)
        return s_enemyBar;

    return s_playerBar;
}
void HpBar::SetHp(int hp)
{
    m_hp = hp;

    if (m_hp < 0)
        m_hp = 0;

    if (m_hp > m_maxHp)
        m_hp = m_maxHp;
}