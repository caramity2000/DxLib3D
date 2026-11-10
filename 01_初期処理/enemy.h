#pragma once
#include "model.h"
#include "sprite.h"

//敵クラス(ﾓﾃﾞﾙｸﾗｽを継承)
class Enemy : public Model
{
public:
	Enemy();
	~Enemy();

	void Init();	// 初期化処理
	void Init(int index);	// 初期化処理(ｵｰﾊﾞｰﾛｰﾄﾞ関数)
	void Update();	// 更新処理
	void Draw();	// 表示処理

	void TakeDamage(int index ,int damage);	//体力を減らす
	int GetHp(int index);	//体力を取得

	// 位置の取得
	inline VECTOR getPosition(int index)
	{
		return enemyPos[index];
	}
	// プレイヤーの位置を設定
	inline void setPlayerPos(VECTOR pos)
	{
		playerPos = pos;
	}

	static const int ENEMYMAX = 10;	// 敵の最大数

private:
	const float SPEED = 0.4f;	// 移動速度
	
	VECTOR enemyPos[ENEMYMAX];	// 敵の位置
	DIRECTION dir[ENEMYMAX];	// 敵の向き
	bool isDead[ENEMYMAX];		// 死亡ﾌﾗｸﾞ
	float fYaw[ENEMYMAX];		// Y軸回転値
	//Yaw(ヨー):Y軸回転
	//Pitch(ピッチ):X軸回転
	//Roll(ロール):Z軸回転

	int hp[ENEMYMAX];
	int maxHp;
	Sprite* hpGauge;
	
	VECTOR playerPos;		//プレイヤーの位置
	void initPosition(int index);	//初期位置の設定

};
