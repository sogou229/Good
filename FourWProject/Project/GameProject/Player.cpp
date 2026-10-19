
#include "Player.h"
#include "PlayerAttack.h" 
#include"HpBar.h"



Player::Player(const CVector2D& pos, bool flip)
	: Base(eType_Player)
	, m_state(0)
	, m_attack_cnt(0)
	, m_down_cnt(0)
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


	//プレイヤーの当たり判定
	m_rect = CRect(-50, -100, 50, 0);

	m_img.SetCenter(200, 350);



	m_isGuard = false;

}
void Player::Update()
{
	// HPが0になったとき
	if (m_state == eState_Down)
	{
		m_down_cnt++;

		// 上に移動する
		m_pos.y -= 2.0f;

		// 60フレーム経過したら消す
		if (m_down_cnt >= 60)
		{
			SetKill();
		}

		return;
	}
	// アニメーションの更新
	m_img.UpdateAnimation();

	// 更新前の座標を確認
	float oldX = m_pos.x;
	float oldY = m_pos.y;

	// 重力
	m_vec.y += 0.5f;
	m_pos.y += m_vec.y;

	// 地面
	if (m_pos.y > 800)
	{
		m_pos.y = 800;
		m_vec.y = 0;
		m_is_ground = true;
	}
	else
	{
		m_is_ground = false;
	}


	// Xキーはガード
	if (GetAsyncKeyState('X') & 0x8000)
	{
		m_isGuard = true;
	}
	else
	{
		m_isGuard = false;
	}
	
	if (m_isGuard)
	{
		m_img.ChangeAnimation(eAnimGuard);
		return;
	}
	
	//ジャンプ
	if (PUSH(CInput::eButton5) && m_is_ground)
	{
		m_vec.y = -15;
		m_is_ground = false;

		// ジャンプ音を再生
		SOUND("Jump")->Play();
	}
	
	// 攻撃
	if (PUSH(CInput::eButton1) && m_state != eState_Attack)
	{
		m_state = eState_Attack;
		m_attack_cnt = 0;
		m_img.ChangeAnimation(eAnimAttack, false);

		// 剣の攻撃音を再生
		SOUND("PlayerSlash")->Play();

		new PlayerAttack(m_pos+CVector2D(0,-100), m_flip);
		
		return;
	}

	// 攻撃中
	if (m_state == eState_Attack)
	{
		m_attack_cnt++;

		if (m_attack_cnt >= 18)
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
	// ステージ左右の端
	if (m_pos.x < 0)
	{
		m_pos.x = 0;
	}

	if (m_pos.x > 1600)
	{
		m_pos.x = 1600;
	}
	
}

void Player::Draw()
{
	// 画面上の座標を取得
	CVector2D screenPos = GetScreenPos(m_pos);

	// 画像の位置を設定
	m_img.SetPos(screenPos);

	// 左右反転
	m_img.SetFlipH(m_flip);

	// プレイヤーを描画
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
	{ 32,3 },
	{ 33,3 },
	{ 34,3 },
	{ 35,3 },
	{ 36,3 },
	{ 37,3 },
	{ 38,3 },
};

static TexAnim _Guard[] = {
	{ 48 ,3 },
};

TexAnimData Player::_anim_data[] = {
	ANIMDATA(_idle),
	ANIMDATA(_run),
	ANIMDATA(_attack),
	ANIMDATA(_Guard),
};

void Player::Collision(Base* b) {

}
void Player::Damage(int damage)
{
	// ガード中ならダメージを受けない
	if (m_isGuard)
	{
		return;
	}

	m_hp -= damage;

	if (m_hp <= 0)
	{
		m_hp = 0;
		m_state = eState_Down;
		m_down_cnt = 0;
	}

	HpBar* bar = HpBar::GetBar(false);

	if (bar != nullptr)
	{
		bar->SetHp(m_hp);
	}
	


	//printf("Player HP: %d\n", m_hp);


}