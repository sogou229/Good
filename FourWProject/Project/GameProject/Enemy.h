#pragma once
#include "Base/Base.h"

class Enemy :public Base {
private:
	enum {
		eState_Idle,
		eState_Down
	};
	//ó‘Ô•Ï”
	CImage m_img;
	bool m_flip;
	int m_hp;
	int m_down_cnt;
	int m_state;
public:
	Enemy(const CVector2D& pos);
	void Update();
	void Draw();
	void Damage(int damage);
	static TexAnimData _anim_data[];
};
