#include "Stage.h"
#include "Player.h"

Stage::Stage() :Base(eType_Stage) {
	m_stage = COPY_RESOURCE("Stage", CImage);
	m_ground_y = 500;
	m_left_x = 0.0f;
	m_right_x = 1920.0f;
}
void Stage::Draw() {
	//m_stage.SetSize(1920, 1080);
	// ステージ画像の位置を設定
	//m_stage.SetPos(GetScreenPos(m_pos));
	m_stage.SetSize(1920, 1080);
	m_stage.SetCenter(960, 540);
	m_stage.SetPos(CVector2D(960, 540));
	// ステージ画像を描画
	//m_stage.Draw();
}