#include "camera.h"

// ｺﾝｽﾄﾗｸﾀ
Camera::Camera()
	:cameraPos(VGet(0, 10.0f, -100.0f)),
	 lookPos(VGet(0, 5.0f, 100.0f))
{
	//cameraPos = VGet(0, 10.0f, -100.0f);
	//lookPos = VGet(0, 5.0f, 100.0f);

	// カメラの有効範囲の設定
	SetCameraNearFar(1.0f, 1000.0f);
	// カメラ位置と注視位置の設定
	SetCameraPositionAndTarget_UpVecY(cameraPos, lookPos);
}
// ﾃﾞｽﾄﾗｸﾀ
Camera::~Camera()
{
}
//カメラ位置の設定
void Camera::setCamera(VECTOR cameraPos, VECTOR lookPos) {

	//カメラ位置と注視位置の設定
	this->cameraPos = cameraPos;
	this->lookPos = lookPos;
	SetCameraPositionAndTarget_UpVecY(cameraPos, lookPos);
}
// カメラの移動
void Camera::moveCamera()
{
	if (CheckHitKey(KEY_INPUT_UP) == 1)cameraPos.y += CAMERA_SPEED;
	if (CheckHitKey(KEY_INPUT_LEFT) == 1)cameraPos.x -= CAMERA_SPEED;
	if (CheckHitKey(KEY_INPUT_DOWN) == 1)cameraPos.y -= CAMERA_SPEED;
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1)cameraPos.x += CAMERA_SPEED;
	if (CheckHitKey(KEY_INPUT_N) == 1)cameraPos.z -= CAMERA_SPEED;
	if (CheckHitKey(KEY_INPUT_M) == 1)cameraPos.z += CAMERA_SPEED;

	SetCameraPositionAndTarget_UpVecY(cameraPos, lookPos);
}

// 注視位置(Target)の移動
void Camera::moveLook()
{
	if (CheckHitKey(KEY_INPUT_I) == 1)lookPos.y += CAMERA_SPEED;
	if (CheckHitKey(KEY_INPUT_J) == 1)lookPos.x -= CAMERA_SPEED;
	if (CheckHitKey(KEY_INPUT_K) == 1)lookPos.y -= CAMERA_SPEED;
	if (CheckHitKey(KEY_INPUT_L) == 1)lookPos.x += CAMERA_SPEED;
	if (CheckHitKey(KEY_INPUT_U) == 1)lookPos.z -= CAMERA_SPEED;
	if (CheckHitKey(KEY_INPUT_O) == 1)lookPos.z += CAMERA_SPEED;

	SetCameraPositionAndTarget_UpVecY(cameraPos, lookPos);
}
