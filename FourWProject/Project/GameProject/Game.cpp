#include"Game.h"
#include"Title.h"
#include"Enemy.h"
#include"Player.h"
#include"GameClear.h"
#include"GameOver.h"
#include"HpBar.h"
#include"Stage.h"

Game::Game() :Base(eType_Scene)
{
	// ステージ
	new Stage();
	new Player(CVector2D(300, 526), false);
	new Enemy(CVector2D(1560, 616)); //y616

	// プレイヤー
	//new Player(CVector2D(500, 700), false);

	// 敵
	//new Enemy(CVector2D(1400, 700));

	// HPバー
	new HpBar(false, 100);  // プレイヤーHP
	new HpBar(true, 100);   // 敵HP
	m_cnt = 0;

	SOUND("BGM")->Play(true);
}
void Game::Update()
{
	// プレイヤーが死亡したらGameOver
	if (!Base::FindObject(eType_Player))
	{
		Base::KillAll();
		new GameOver();
		return;
	}
	//敵が死亡したらGameClear
	else if (!Base::FindObject(eType_Enemy))
	{
		Base::KillAll();
		new GameClear();
		return;
	}
}