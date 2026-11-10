#pragma once
#include "common.h"

// カメラクラス
class Camera
{
public:
	Camera();	// ｺﾝｽﾄﾗｸﾀ
	~Camera();	// ﾃﾞｽﾄﾗｸﾀ

	void moveCamera();	// ｶﾒﾗの移動
	void moveLook();	// 注視位置(Target)の移動

	//カメラ位置の設定
	void setCamera(VECTOR cameraPos, VECTOR lookPos);

private:

	VECTOR cameraPos;	// ｶﾒﾗ位置
	VECTOR lookPos;		// 注視位置

	const float CAMERA_SPEED = 1.0f;//移動速度
};