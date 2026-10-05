#include "Enemy.h"

Enemy::Enemy(const CVector2D& pos)
	: Base(eType_Enemy)
	, m_flip(false)
	, m_hp(100)
	, m_down_cnt(0)
	, m_state(eState_Idle)
{
	m_img = COPY_RESOURCE("Enemy", CImage);
	m_pos = pos;

	m_img.SetSize(400, 400);
	// 再生アニメーション
	m_img.ChangeAnimation(0);

	m_rect = CRect(-50, -100, 50, 0);
}

void Enemy::Update()
{
	if (m_state == eState_Down)
	{
		m_down_cnt++;

		m_pos.y += -2.0f;

		if (m_down_cnt >= 60)
		{
			SetKill();
		}

		return;
	}

	m_vec.y += 0.5f;
	m_pos.y += m_vec.y;

	if (m_pos.y > 390)
	{
		m_pos.y = 390;
	}

	m_img.UpdateAnimation();

	Base* player = FindObject(eType_Player);

	if (player != nullptr)
	{
		float distance = player->m_pos.x - m_pos.x;

		if (distance > 50.0f)
		{
			// プレイヤーが右にいる
			m_pos.x += 3.0f;
			m_flip = false;

			m_img.ChangeAnimation(1);
		}
		else if (distance < -50.0f)
		{
			// プレイヤーが左にいる
			m_pos.x -= 3.0f;
			m_flip = true;

			m_img.ChangeAnimation(1);
		}
		else
		{
			// プレイヤーに近づいたら待機
			m_img.ChangeAnimation(0);
		}
	}
}

void Enemy::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipH(m_flip);
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

static TexAnim _run[]{
	{ 10,2 },
	{ 11,2 },
	{ 12,2 },
	{ 13,2 },
	{ 14,2 },
	{ 15,2 },
	{ 16,2 },
	{ 17,2 },
	{ 18,2 },
};

TexAnimData Enemy::_anim_data[] = {
	ANIMDATA(_idle),
	ANIMDATA(_run),
};

void Enemy::Damage(int damage)
{
	m_hp -= damage;

	printf("Enemy HP: %d", m_hp);

	if (m_hp <= 0)
	{
		m_state = eState_Down;
		m_down_cnt = 0;
	}
}