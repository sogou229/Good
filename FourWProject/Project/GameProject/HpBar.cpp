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
    
}


void HpBar::Draw()
{
    float rate = 0.0f;

    if (m_maxHp > 0)
    {
        rate = (float)m_hp / (float)m_maxHp;
    }

    if (rate < 0.0f) rate = 0.0f;
    if (rate > 1.0f) rate = 1.0f;

    // HPバー全体のサイズ
    float maxWidth = 650.0f;
    float height = 217.0f;

    // HPバー全体を描画
    m_img.SetSize(maxWidth, height);
    m_img.SetCenter(0, 0);

    float barX = m_isEnemy ? 1270.0f : 20.0f;

    m_img.SetPos(CVector2D(barX, 25.0f));
    m_img.Draw();

    float gaugeLeft;
    float gaugeRight;
    float gaugeTop = 121.6f;
    float gaugeHeight = 30.0f;
   

    if (m_isEnemy)
    {
        // 敵側：ここは変更しない
        gaugeLeft = barX + 43.0f;
        gaugeRight = barX + maxWidth - 75.0f;
    }
    else
    {
        // プレイヤー側だけ調整
        gaugeLeft = 110.0f;
        gaugeRight = 637.5f;
    }

    float gaugeWidth = gaugeRight - gaugeLeft;
    float lostWidth = gaugeWidth * (1.0f - rate);

    if (lostWidth > 0.0f)
    {
        float coverX;

        if (m_isEnemy)
        {
            // 敵：左から右へ減らす（元の処理）
            coverX = gaugeLeft;
        }
        else
        {
            // プレイヤー：右から左へ減らす
            coverX = gaugeRight - lostWidth;
        }

        Utility::DrawQuad(
            CVector2D(coverX, m_isEnemy ? gaugeTop : gaugeTop + 5.0f),
            CVector2D(lostWidth, gaugeHeight),
            CVector4D(0, 0, 0, 1)
        );
    }
}


void HpBar::Damage(int hp)
{
    m_hp -= hp;

    if (m_hp < 0)
        m_hp = 0;

    if (m_hp > m_maxHp)
        m_hp = m_maxHp;

    float rate = 0.0f;
    // 減ったHPの幅
    float lostWidth = 650.0f * (1.0f - rate);

    // ゲージ部分だけを黒く隠す
    if (lostWidth > 0.0f)
    {
        float coverX;

        if (m_isEnemy)
        {
            // 敵：左から減らす
            coverX = 1270.0f + 105.0f;
        }
        else
        {
            // プレイヤー：右から減らす
            coverX = 20.0f + 650.0f - 105.0f - lostWidth;
        }

        Utility::DrawQuad(
            CVector2D(coverX, 25.0f + 100.0f),
            CVector2D(lostWidth, 40.0f),
            CVector4D(0, 0, 0, 1)
        );
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