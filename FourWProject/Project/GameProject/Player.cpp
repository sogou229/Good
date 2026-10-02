#include "Player.h"


Player::Player(const CVector2D& pos, bool flip)
	: Base(eType_Player)
	, m_state(0)
	, m_hp(100)
	, m_is_ground(true)
	, m_isFlip(false)
{
	// 画像複製
	m_img = COPY_RESOURCE("Player", CImage);

	// 反転フラグ
	m_flip = flip;

	// 座標設定
	m_pos = pos;

	m_img.SetSize(200, 200);
	m_img.ChangeAnimation(0);
}

void Player::Update()
{

	//アニメーションの更新
	m_img.UpdateAnimation();

	// 右移動
    if (CInput::HOLD(CInput::eRight))
    {
        m_pos.x += 5.0f;
		m_flip = false;
		m_img.ChangeAnimation(1);
		
    }

    // 左移動
	else if (CInput::HOLD(CInput::eLeft))
    {
        m_pos.x -= 5.0f;
		m_flip = true;
		m_img.ChangeAnimation(1);
    }

	 // 動いていない
	 else
	 {
		 m_img.ChangeAnimation(0);
	 }
	 
}

void Player::Draw()
{
	//位置設定
	m_img.SetPos(GetScreenPos(m_pos));
	
	//左右反転
	m_img.SetFlipH(m_flip);
	
	//描画
	m_img.Draw();
	
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
static TexAnim _run[] = {
	{ 16,2 },
	{ 17,2 },
	{ 18,2 },
	{ 19,2 },
	{ 20,2 },
	{ 21,2 },
	{ 22,2 },
	{ 23,2 },
	{ 24,2 },
	{ 25,2 },
};
TexAnimData Player::_anim_data[] = {
	ANIMDATA(_idle),//eAnimIdle=0
	ANIMDATA(_run),
};
void Player::Collision(Base* b) {

}

