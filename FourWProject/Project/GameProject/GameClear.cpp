#include "GameClear.h"
#include "Game.h"
#include "Title.h"
GameClear::GameClear() :Base(eType_Scene) 
{
	m_img = COPY_RESOURCE("GameClear", CImage);
}
void GameClear::Update()
{
	//　ボタン１でゲームシーン終了
	if (PUSH(CInput::eButton1)) {
		//全てのオブジェクトを破棄
		Base::KillAll();
		//タイトルシーンへ
		//new Title();
	}
}
void GameClear::Draw()
{
	m_img.Draw();
	m_img.SetSize(1900, 1080);
}