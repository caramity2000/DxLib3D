#include "common.h"
#include "gameManager.h"
#include "fps.h"

int WINAPI WinMain(
	HINSTANCE, HINSTANCE, LPSTR, int)
{
	SetWindowText("3Dシューティングゲーム");
	ChangeWindowMode(TRUE);		// ｳｨﾝﾄﾞｳﾓｰﾄﾞで起動
	SetGraphMode(WND_W, WND_H, COLOR_BIT);// 画面ｻｲｽﾞ1280x720

	if (DxLib_Init() == -1)return -1;// Dxﾗｲﾌﾞﾗﾘ初期化

	SetBackgroundColor(0, 0, 0);	// ｳｨﾝﾄﾞｳ背景色
	SetDrawScreen(DX_SCREEN_BACK);	// 裏画面に表示
	SetUseZBuffer3D(TRUE);			// Z領域を使用する
	SetWriteZBuffer3D(TRUE);		// Z領域に書込みを許可

	// クラス宣言
	class Fps			fps;			// FPSｸﾗｽ
	class GameManager	gameManager;	// ｹﾞｰﾑﾏﾈｰｼﾞｬｰｸﾗｽ

	gameManager.Init();	//ｹﾞｰﾑの初期化

	//ゲームループ
	while (true)
	{
		ClearDrawScreen();	// 画面のｸﾘｱ

		gameManager.Update();	//ｹﾞｰﾑの更新
		gameManager.Draw();		//ｹﾞｰﾑの表示

		fps.update();
		fps.draw();
		ScreenFlip();	// 裏画面を表示
		fps.wait();

		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)break;//ESCｷｰで終了
		//ｳｨﾝﾄﾞｳが閉じた時(×ﾎﾞﾀﾝ等)終了
		if (ProcessMessage() == -1)break;	
	}

	DxLib_End();	// Dxﾗｲﾌﾞﾗﾘの終了
	return 0;
}