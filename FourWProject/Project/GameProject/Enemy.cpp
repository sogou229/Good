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
	, m_wait_cnt(0)
	,m_jump_cnt(0)
	,m_jump_time(120+rand()%181)
	
{
	m_img = COPY_RESOURCE("Enemy", CImage);
	m_pos = pos;

	m_img.SetSize(400, 400);//300

	m_img.SetCenter(200, 250);
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

	//重力
	m_vec.y += 0.5f;
	m_pos.y += m_vec.y;

	//地面に着地したとき
	if (m_pos.y > 800)
	{
		m_pos.y = 800;
		m_vec.y = 0.0f;
		m_is_ground = true;
	}



	m_img.UpdateAnimation();

	Base* player = FindObject(eType_Player);
	
	// ランダムジャンプ
	if (m_is_ground)
	{
		m_jump_cnt++;

		// ランダムな時間が経過したらジャンプ
		if (m_jump_cnt >= m_jump_time)
		{
			m_vec.y = -15.0f;
			m_is_ground = false;

			// カウンターをリセット
			m_jump_cnt = 0;

			// 次のジャンプまでの時間（90～300フレーム）
			m_jump_time = 90 + rand() % 181;
		}
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
			m_wait_cnt++;

			//攻撃
			if (m_state == eState_Idle && m_wait_cnt >= 60)
			{
				m_state = eState_Attack;
				m_attack_cnt = 0;
				m_wait_cnt = rand()%120;

				m_img.ChangeAnimation(2);

				SOUND("EnemySlash")->Play();

				new EnemyAttack(m_pos, m_flip);
			}
	
		}
		// プレイヤーとの距離
		//float distance = abs(player->m_pos.x - m_pos.x);

		// ガード処理
		if (m_isGuard)
		{
			m_guard_cnt--;

			m_img.ChangeAnimation(4);

			if (m_guard_cnt <= 0)
			{
				m_isGuard = false;
				m_img.ChangeAnimation(0);
			}
		}
		else
		{
			if (abs(player->m_pos.x - m_pos.x) < 250.0f)
			{
				if (rand() % 100 < 3)
				{
					m_isGuard = true;
					m_guard_cnt = 30;

					m_img.ChangeAnimation(4);
				}
			}
		}
	}
}

void Enemy::Draw()
{

		m_img.SetPos(GetScreenPos(m_pos));
		m_img.SetFlipH(m_flip);
		m_img.Draw();
		//DrawRect();
}

void Enemy::Damage(int damage)
{

	// すでに死亡状態なら何もしない
	if (m_state == eState_Down)
		return;

	printf("Enemy HP: %d\n", m_hp);
	printf("Enemy HP after damage: %d\n", m_hp);
	printf("Enemy State: %d\n", m_state);
	printf("Bar HP: %d\n",
		HpBar::GetBar(true) != nullptr
		? HpBar::GetBar(true)->GetHp()
		: -1);

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

	//printf("Enemy HP: %d\n", m_hp);

	if (m_hp <= 0)
	{
		m_state = eState_Down;
		m_down_cnt = 0;
	}

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
static TexAnim _guard[]{
	{ 40,6 },
};
TexAnimData Enemy::_anim_data[] = {
	ANIMDATA(_idle),
	ANIMDATA(_run),
	ANIMDATA(_attack),
	ANIMDATA(_jump),
	ANIMDATA(_guard),
};


