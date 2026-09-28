#include "Player.h"

Player::Player(const CVector2D& pos, bool flip) :
	Base(eType_Player) {
	//‰æ‘œ•¡»
	m_img = COPY_RESOURCE("Player", CImage);
	m_flip = flip;
	m_pos = pos;
}

void Player::Update()
{

}

void Player::Draw()
{
	m_img.Draw();
}
