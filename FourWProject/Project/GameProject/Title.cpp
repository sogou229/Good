/*
#include "Title.h"
#include "Player.h"
#include "Stage.h"
#include "HpBar.h"
Title::Title(): Base(eType_Title)
{
    // タイトル画像を読み込む
    m_img.Load("Image/Title.png");
    m_img.SetSize(1920, 1080);
    m_img.SetCenter(960, 540);

    // 操作説明UI画像を読み込む
    m_UI.Load("Image/UI.png");
    m_UI.SetSize(480, 270);
    m_UI.SetCenter(240, 135);

    m_pos = CVector2D(960, 540);
}

void Title::Update()
{
    if (GetAsyncKeyState('Z') & 0x0001)
    {
        

        // HPバーをゲーム開始時に生成
        new HpBar(false, 100);
        new HpBar(true, 100);
        // タイトル画面を削除する
        SetKill();
    }
}

void Title::Draw()
{
    if (m_start)
    {
        return;
    }
    m_img.SetPos(CVector2D(960, 540));

    m_img.SetPos(m_pos);
    m_img.Draw();

    m_UI.SetPos(CVector2D(950, 750));
    m_UI.Draw();
}
*/