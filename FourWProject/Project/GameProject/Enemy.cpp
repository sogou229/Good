#include "Enemy.h"

Enemy::Enemy(const CVector2D& pos) : Base(eType_Enemy)
{
	m_img = COPY_RESOURCE("Enemy", CImage);
}

void Enemy::Update() {

}
void Enemy::Draw() {

}