#pragma once
#include "common.h"
#include "text.h"
#include "sound.h"

// ゲームマネージャークラス
class GameManager : public Text
{
public:
	GameManager();	//ｺﾝｽﾄﾗｸﾀ(初期処理)
	~GameManager();	//ﾃﾞｽﾄﾗｸﾀ(終了処理)

	void Init();	//初期化処理
	void Update();	//更新処理
	void Draw();	//表示処理

	// 球の当たり判定(計算版)
	bool hitCheck_Sphere(
		VECTOR center1, float r1,	// Aの中心座標と半径
		VECTOR center2, float r2);	// Bの中心座標と半径

	// 球の当たり判定
	bool hitCheck_Sphere(int MHandle, VECTOR pos, float r);

	//カプセルの当たり判定
	bool hitCheck_Capsule(int MHandle,VECTOR pos1, VECTOR pos2, float r);

	//線の当たり判定
	bool hitCheck_Line(int MHandle, VECTOR startPos, VECTOR endPos, VECTOR* crossPos);

private:
	int score;		//点数
	SCENE oldScene;	//変更前のｼｰﾝ

	Sound* explosionSE;	//爆発音

	//線の判定確認用
	bool isHit;			//判定ﾌﾗｸﾞ
	char dbgMsg[128];	//ﾃﾞﾊﾞｯｸﾞﾒｯｾｰｼﾞ
};

