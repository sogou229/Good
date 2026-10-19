#pragma once
#include "Base/Base.h"

class Enemy :public Base {
private:
	enum {
		eState_Idle,
		eState_Down,
		eState_Attack,
		eState_Jump,

	};
	//ó‘Ô•Ï”
	CImage m_img;
	bool m_flip;
	bool m_isGuard;
	int m_guard_cnt = 0;
	CImage m_guardImg;
	int m_hp;
	//’…’nƒtƒ‰ƒO
	bool m_is_ground;
	int m_down_cnt;
	int m_attack_cnt;
	int m_wait_cnt;
	int m_state;
public:
	Enemy(const CVector2D& pos);
	void Update();
	void Draw();
	void Damage(int damage);
	static TexAnimData _anim_data[];
};
