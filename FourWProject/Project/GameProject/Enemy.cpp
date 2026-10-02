#include "Enemy.h"

Enemy::Enemy(const CVector2D& pos) : Base(eType_Enemy)
{
	m_img = COPY_RESOURCE("Enemy", CImage);
	m_pos = pos;
	//再生アニメーション
	m_img.ChangeAnimation(0);
	//体力の初期化
	

}

void Enemy::Update() {
	m_img.UpdateAnimation();
}
void Enemy::Draw() {
	m_img.Draw();
}

static TexAnim _idle[]{
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
TexAnimData Enemy::_anim_data[] = {
	ANIMDATA(_idle),//eAnimIdle=0
	//ANIMDATA(_run),
};
