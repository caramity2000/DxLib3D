#pragma once
#include "common.h"

//サウンドクラス
class Sound
{
public:
	Sound();	//ｺﾝｽﾄﾗｸﾀ
	~Sound();	//ﾃﾞｽﾄﾗｸﾀ

	// サウンド読込み
	bool loadSound(const char* fileName);

	// サウンド再生
	void playSound(bool isLoop);

	// サウンドの停止
	void stopSound();

	// ボリューム(音量)の調整
	void changeVolume(int volume);

private:
	int SHandle;	//ｻｳﾝﾄﾞﾊﾝﾄﾞﾙ
};