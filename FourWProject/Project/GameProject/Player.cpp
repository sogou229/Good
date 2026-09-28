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
}

void Player::Update()
{

}

void Player::Draw()
{
	//位置設定
	m_img.SetPos(GetScreenPos(m_pos));
	//描画
	m_img.Draw();
	//DrawRect();
}
