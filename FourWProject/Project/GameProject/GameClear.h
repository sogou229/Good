#pragma once
#include "Base/Base.h"

class GameClear :public Base {
	CImage m_img;
public:
	GameClear();
	void Update();
	void Draw();
};