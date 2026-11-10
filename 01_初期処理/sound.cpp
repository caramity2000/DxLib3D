#include "sound.h"

Sound::Sound()	// ｺﾝｽﾄﾗｸﾀ
{
}
Sound::~Sound()	// ﾃﾞｽﾄﾗｸﾀ
{
	// ｻｳﾝﾄﾞﾊﾝﾄﾞﾙの削除
	DeleteSoundMem(SHandle);
}

// サウンド読込み
bool Sound::loadSound(const char* fileName)
{
	SHandle = LoadSoundMem(fileName);
	if (SHandle == -1)
	{
		ErrMsg("サウンドの読込み失敗", fileName);
		return false;
	}
	return true;
}

// サウンド再生
void Sound::playSound(bool isLoop)
{
	int playType = DX_PLAYTYPE_BACK;	//ﾊﾞｯｸｸﾞﾗｳﾝﾄﾞ再生
	if (isLoop) {
		playType |= DX_PLAYTYPE_LOOP;	//ﾙｰﾌﾟ再生を追加
	}
	PlaySoundMem(SHandle, playType, TRUE);
}

// サウンドの停止
void Sound::stopSound()
{
	StopSoundMem(SHandle);
}

// ボリューム(音量:0～255)の調整
void Sound::changeVolume(int volume)
{
	ChangeVolumeSoundMem(volume, SHandle);
}
