#pragma once
#include "Base/Base.h"

class Player :public Base {
private:
	enum
	{
		eState_Normal,
		eState_Attack,
		eState_Jump,
		eState_Damage,
		eState_Down,
	};

	//プレイヤーのアニメーション
	enum
	{
		eAnimIdle,
		eAnimMove,
		eAnimAttack,
		eAnimDamage,
		eAnimDown,
	};

	//状態変数
	int m_state;
	int m_attack_cnt;

	//アニメーションの種類
	CImage m_img;
	bool m_flip;
	//体力
	int m_hp;
	//着地フラグ
	bool m_is_ground;
	//反転フラグ
	bool m_isFlip;		
	

public:
	Player(const CVector2D& pos, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);
	static TexAnimData _anim_data[];
};