#pragma once
#include "Base/Base.h"
class Stage:public Base{
 private:
	 CImage m_stage;
	 //è∞
	 float m_ground_y;
	 //ç∂âE
	 float m_left_x;
	 float m_right_x;
public:
	Stage();
	void Draw();

	float GetGroundY()const {
		return m_ground_y;
	}
	float GetLeftx()const {
		return m_left_x;
	}
	float GetRightX() const
	{
		return m_right_x;
	}
};