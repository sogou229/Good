
#pragma once
#include "Base/Base.h"

class Title : public Base
{
private:
    CImage m_img;
    CImage m_UI;
    bool m_start;
    int m_cnt;
    bool pushZ;
public:
    Title();

    void Update();
    void Draw();
};
