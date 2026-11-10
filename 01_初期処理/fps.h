#pragma once
#include "Dxlib.h"

// FPS(Frame Per Second)クラス
class Fps
{
public:

	// コンストラクタ
	Fps() : startTime(0), frame(0), fps(0)
	{
		//startTime = 0;
		//frame = 0;
		//fps = 0;
	}

	// 更新処理
	inline bool update()
	{
		if (frame == 0)	// 1ﾌﾚｰﾑ目の時
		{
			startTime = GetNowCount();	//開始時間を取得
		}
		if (frame == N)// 60ﾌﾚｰﾑ目の時
		{
			// 平均を計算する
			int t = GetNowCount();	//現在の時間を取得
			fps = 1000.0f / ((t - startTime) / static_cast<float>(N));
			frame = 0;	//ﾌﾚｰﾑ数初期化
			startTime = t;	//次の60ﾌﾚｰﾑの為に時間を更新
		}
		frame++;	//ﾌﾚｰﾑ数を加算
		return true;
	}

	// (更新時間が来るまで)時間待ち
	inline void wait()
	{
		int tookTime = GetNowCount() - startTime;	//経過時間
		// (ﾌﾚｰﾑ毎の)待つべき時間
		int waitTime = (frame * (1000.0f / FPS)) - tookTime;
		if (waitTime > 0)
		{
			Sleep(waitTime);	//時間まで処理を停止
		}
	}

	// FPS値の表示
	inline void draw()
	{
		DrawFormatString(
			1200, 700,				//表示位置
			GetColor(255, 255, 255),//文字色(白)
			"%0.1f FPS", fps);
	}

private:
	int startTime;	//測定開始時間
	int frame;		//ﾌﾚｰﾑ数
	float fps;		//FPS値
	static const int N = 60;	//平均を取るｻﾝﾌﾟﾙ数
	static const int FPS = 60;	//設定したFPS値

};