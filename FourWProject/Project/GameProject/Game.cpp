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
 
}
void Game::Update()
{
	// ƒvƒŒƒCƒ„[‚ª€–S‚µ‚½‚çGameOver
	if (!Base::FindObject(eType_Player))
	{
		Base::KillAll();
		new GameOver();
		return;
	}
	//“G‚ª€–S‚µ‚½‚çGameClear
	if (!Base::FindObject(eType_Enemy))
	{
		Base::KillAll();
		new GameClear();
		return;
	}
}