#include "Enemy.h"

Enemy::Enemy(const CVector2D& pos)
	: Base(eType_Enemy)
	, m_flip(false)
{
	m_img = COPY_RESOURCE("Enemy", CImage);
	m_pos = pos;

	// 再生アニメーション
	m_img.ChangeAnimation(0);
}

void Enemy::Update()
{
	m_img.UpdateAnimation();

	Base* player = FindObject(eType_Player);

	if (player != nullptr)
	{
		float distance = player->m_pos.x - m_pos.x;

		if (distance > 50.0f)
		{
			// プレイヤーが右にいる
			m_pos.x += 2.0f;
			m_flip = false;

			m_img.ChangeAnimation(1);
		}
		else if (distance < -50.0f)
		{
			// プレイヤーが左にいる
			m_pos.x -= 2.0f;
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