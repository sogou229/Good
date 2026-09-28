/*#include "Title.h"
#include "Player.h"
#include "Stage.h"
Title::Title(): Base(eType_Title)
{
    // タイトル画像を読み込む
    m_img.Load("Image/Title.png");
    m_img.SetSize(1920, 1080);
    m_img.SetCenter(960, 540);
   
    m_pos = CVector2D(960, 540);
}

void Title::Update()
{
    if (GetAsyncKeyState('Z') & 0x0001)
    {
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
}
*/