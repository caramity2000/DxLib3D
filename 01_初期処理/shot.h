#pragma once
#include "model.h"
#include "sound.h"

//弾クラス(ﾓﾃﾞﾙｸﾗｽを継承)
class Shot : public Model
{
public:
	Shot();		//ｺﾝｽﾄﾗｸﾀ
	~Shot();	//ﾃﾞｽﾄﾗｸﾀ

	void Init();	//初期化処理
	void Init(int index);//初期化処理(ｵｰﾊﾞｰﾛｰﾄﾞ関数)
	void Update();	//更新処理
	void Draw();	//表示処理

	void Dir4Shot(int index);	//4方向射撃
	void Dir8Shot(int index);	//8方向射撃

	// プレイヤーの位置を設定
	inline void setPlayerPos(VECTOR pos ,DIRECTION dir)
	{
		playerPos = pos;
		playerDir = dir;
	}
	// 位置の取得
	inline VECTOR getPosition(int index)
	{
		return shotPos[index];
	}

	static const int SHOTMAX = 30;	//弾の最大数

private:
	const float SPEED = 3.0f;	//移動速度

	VECTOR	playerPos;			//ﾌﾟﾚｲﾔｰの位置
	DIRECTION playerDir;		//ﾌﾟﾚｲﾔｰの向き

	VECTOR	shotPos[SHOTMAX];	//弾の座標
	DIRECTION dir[SHOTMAX];		//弾の向き
	bool	isShot[SHOTMAX];	//発射中ﾌﾗｸﾞ
	int		interval;			//弾の間隔

	Sound* shotSE;	//弾を撃つ音
};
