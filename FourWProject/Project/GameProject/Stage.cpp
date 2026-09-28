#include "Stage.h"
#include "Player.h"

Stage::Stage() :Base(eType_Stage) {
	m_stage = COPY_RESOURCE("Stage", CImage);
	m_ground_y = 500;
	m_left_x = 0.0f;
	m_right_x = 1920.0f;
}
void Stage::Draw() {
	// ステージ画像の位置を設定
	m_stage.SetPos(GetScreenPos(m_pos));

	// ステージ画像を描画
	//m_stage.Draw();
}