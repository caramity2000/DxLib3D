#pragma once
#include "DxLib.h"

// 定数宣言
const int WND_W = 1280;		//ｳｨﾝﾄﾞｳ幅
const int WND_H = 720;		//ｳｨﾝﾄﾞｳ高さ
const int COLOR_BIT = 32;	//色数
const float ROOT2 = 1.4142f;//√2

// 関数マクロの定義
#define ErrMsg(s, f) MessageBox(NULL,s,f,MB_OK);
#define ToRadian(x)(x*DX_PI_F/180.0f)	//度→ﾗｼﾞｱﾝ変換

// 画面遷移の列挙体
enum class SCENE
{
	TITLE,	// 0:ﾀｲﾄﾙ
	GAME,	// 1:ｹﾞｰﾑ中
	OVER,	// 2:ｹﾞｰﾑｵｰﾊﾞｰ
	CLEAR,	// 3:ｹﾞｰﾑｸﾘｱ
};

//方向
enum class DIRECTION {

	DOWN,	//0:下（手前向き）
	LEFT,	//1:左
	UP,		//2:上（奥向き）
	RIGHT,	//3:右
	LEFTDOWN,	//4:左下
	LEFTUP,		//5:左上
	RIGHTUP,	//6:右上
	RIGHTDOWN,	//7:右下
};