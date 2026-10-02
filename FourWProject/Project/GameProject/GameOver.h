#pragma once
#include "Base/Base.h"

class GameOver :public Base {
	CImage m_img;
public:
	GameOver();
	void Update();
	void Draw();
};