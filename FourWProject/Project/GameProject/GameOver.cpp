#include "GameOver.h"
#include "Game.h"
#include "Title.h"
GameOver::GameOver() :Base(eType_Scene)
{
	m_img = COPY_RESOURCE("GameOver", CImage);
}
void GameOver::Update()
{
	//　ボタン１でゲームシーン終了
	if (PUSH(CInput::eButton1)) {
		//全てのオブジェクトを破棄
		Base::KillAll();
		//タイトルシーンへ
		//new Title();
	}
}
void GameOver::Draw()
{
	m_img.Draw();
	m_img.SetSize(1900, 1080);
}