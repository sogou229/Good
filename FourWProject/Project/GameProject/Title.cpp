#include "Title.h"
Title::Title(): Base(eType_Title)
{
    // タイトル画像を読み込む
    m_img.Load("Image/Title.png");
    m_img.SetSize(1920, 1080);
    m_img.SetCenter(960, 540);
    m_pos.x = 960;
    m_pos.y = 540;


}

void Title::Update()
{
    // Zキーが押されたら次の画面へ
    if (GetAsyncKeyState('Z') & 0x0001)
    {
        // ここでゲーム画面へ移動
    }
}

void Title::Draw()
{
    m_img.SetPos(m_pos);
    m_img.Draw();
}