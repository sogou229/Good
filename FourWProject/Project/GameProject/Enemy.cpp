#include "Enemy.h"
#include "EnemyAttack.h"
#include "HpBar.h"

Enemy::Enemy(const CVector2D& pos)
	: Base(eType_Enemy)
	, m_flip(false)
	, m_hp(100)
	, m_is_ground(true)
	, m_down_cnt(0)
	, m_attack_cnt(0)
	, m_state(eState_Idle)
	
{
	m_img = COPY_RESOURCE("Enemy", CImage);
	m_pos = pos;

	m_img.SetSize(400, 400);//300
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

	if (m_state == eState_Attack)
	{
		m_img.UpdateAnimation();

		static int attack_cnt = 0;
		attack_cnt++;

		if (attack_cnt >= 18)
		{
			attack_cnt = 0;
			m_state = eState_Idle;
			m_img.ChangeAnimation(0);
		}

		return;
	}

	m_vec.y += 0.5f;
	m_pos.y += m_vec.y;

	if (m_pos.y > 616)
	{
		m_pos.y = 616;
	}

	m_vec.y += 0.5f;
	m_pos.y += m_vec.y;

	if (m_pos.y > 616)
	{
		m_pos.y = 616;
	}

	m_img.UpdateAnimation();

	Base* player = FindObject(eType_Player);
	
	if (PUSH(CInput::eUp) && m_is_ground)
	{
		m_vec.y = -15.0f;
		m_is_ground = false;
		
	}
	
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

			//攻撃
			if (m_state == eState_Idle)
			{
				m_attack_cnt++;

				if (m_attack_cnt >= 15)
				{
					m_state = eState_Attack;
					m_attack_cnt = 0;
				}

				m_img.ChangeAnimation(2);

				new EnemyAttack(m_pos, m_flip);
			}
			
		}
		// プレイヤーとの距離
		//float distance = abs(player->m_pos.x - m_pos.x);

		// 近距離では一定確率でガードする例
		if (distance < 250.0f && rand() % 100 < 3)
		{
			m_isGuard = true;
		}
		else
		{
			m_isGuard = false;
		}
		
		// プレイヤーとの距離が近いとき、CPUがガードする
		if (abs(player->m_pos.x - m_pos.x) < 250.0f)
		{
			if (rand() % 100 < 3)
			{
				m_isGuard = true;
			}
		}
		else
		{
			m_isGuard = false;
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
static TexAnim _attack[]{
	{ 19,6 },
	{ 20,6 },
	{ 21,6 },
};
static TexAnim _jump[]{
	{ 29,6 },
	{ 30,6 },
	{ 31,6 },
	{ 32,6 },
	{ 33,6 },
	{ 34,6 },
};
TexAnimData Enemy::_anim_data[] = {
	ANIMDATA(_idle),
	ANIMDATA(_run),
	ANIMDATA(_attack),
	ANIMDATA(_jump),
};

void Enemy::Damage(int damage)
{
	// ガード中はダメージを4分の1にする
	if (m_isGuard)
	{
		damage /= 4;
	}

	m_hp -= damage;

	if (m_hp < 0)
		m_hp = 0;

	HpBar* bar = HpBar::GetBar(true);

	if (bar != nullptr)
	{
		bar->SetHp(m_hp);
	}

	/*printf("Enemy HP: %d\n", m_hp);

	if (m_hp <= 0)
	{
		m_state = eState_Down;
		m_down_cnt = 0;
	}
	*/
}