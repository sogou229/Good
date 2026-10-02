#include "Player.h"


Player::Player(const CVector2D& pos, bool flip)
	: Base(eType_Player)
	, m_state(0)
	, m_attack_cnt(0)
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

	m_img.SetSize(400, 400);
	m_img.ChangeAnimation(0);
}

void Player::Update()
{
	// アニメーションの更新
	m_img.UpdateAnimation();

	// 攻撃
	if (PUSH(CInput::eButton1))
	{
		m_state = eState_Attack;
		m_attack_cnt = 0;
		m_img.ChangeAnimation(eAnimAttack, false);
		return;
	}

	// 攻撃中
	if (m_state == eState_Attack)
	{
		m_attack_cnt++;

		if (m_attack_cnt >= 20)
		{
			m_state = eState_Normal;
			m_img.ChangeAnimation(eAnimIdle);
		}

		return;
	}

	// 右移動
	if (HOLD(CInput::eRight))
	{
		m_pos.x += 5.0f;
		m_flip = false;
		m_img.ChangeAnimation(eAnimMove);
	}

	// 左移動
	else if (HOLD(CInput::eLeft))
	{
		m_pos.x -= 5.0f;
		m_flip = true;
		m_img.ChangeAnimation(eAnimMove);
	}

	// 動いていない
	else
	{
		m_img.ChangeAnimation(eAnimIdle);
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
	{ 26,2 },
	{ 27,2 },
	{ 28,2 },
	{ 29,2 },
	{ 30,2 },
	{ 31,2 },
};

static TexAnim _attack[] = {
	{ 32,2 },
	{ 33,2 },
	{ 34,2 },
	{ 35,2 },
	{ 36,2 },
	{ 37,2 },
	{ 38,2 },
};

TexAnimData Player::_anim_data[] = {
	ANIMDATA(_idle),
	ANIMDATA(_run),
	ANIMDATA(_attack),
};
void Player::Collision(Base* b) {

}

