#include "Player.h"


Player::Player(const CVector2D& pos, bool flip) :
	Base(eType_Player) {
	//画像複製
	m_img = COPY_RESOURCE("Player", CImage);
	//反転フラグ
	m_flip = flip;
	//座標設定
	m_pos = pos;
	m_img.SetSize(200, 200);
	m_img.ChangeAnimation(0);
}

void Player::Update()
{
	//アニメーションの更新
	m_img.UpdateAnimation();
}

void Player::Draw()
{
	//位置設定
	m_img.SetPos(GetScreenPos(m_pos));
	//描画
	m_img.Draw();
	//DrawRect();
}

static TexAnim _idle[] = {
	{ 0,2 },
	{ 1,2 },
	{ 2,2 },
	{ 3,2 },
	{ 4,2 },
	{ 5,2 },
	{ 6,2 },
	{ 7,2 },
	{ 8,2 },
	{ 9,2 },
};

TexAnimData Player::_anim_data[] = {
	ANIMDATA(_idle),//eAnimIdle=0
	//ANIMDATA(_run),
};

