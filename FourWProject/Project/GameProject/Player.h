#pragma once
#include "Base/Base.h"

class Player :public Base {
private:
	CImage m_img;
	
	bool m_flip;
public:
	Player(const CVector2D& pos, bool flip);
	void Update();
	void Draw();
	static TexAnimData _anim_data[];
};