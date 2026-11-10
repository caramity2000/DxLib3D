#pragma once
#include "model.h"
#include "sprite.h"

//プレイヤークラス(ﾓﾃﾞﾙｸﾗｽを継承)
class Player : public Model
{
public:
	Player();	//ｺﾝｽﾄﾗｸﾀ
	~Player();	//ﾃﾞｽﾄﾗｸﾀ

	void Init();	//初期化処理
	void Update();	//更新処理
	void Draw();	//表示処理

	void DrawTitle();	// ﾀｲﾄﾙ画面用
	void DrawOver();	// ｹﾞｰﾑｵｰﾊﾞｰ画面用
	void DrawClear();	//ｹﾞｰﾑｸﾘｱ画面用

	void Dir4Move();	//4方向移動
	void Dir8Move();	//8方向移動

	bool GetDeadCnt();			// 死亡時のｶｳﾝﾄ処理
	void SetIsDead(int deadCnt);// 死亡ﾌﾗｸﾞの設定

	void TakeDamage();	//残機数を減らす
	void TakeDamage(int damage);	//体力を減らす

	//死亡中フラグ取得
	inline bool GetIsDead() {
		return isDead;
	}

	//残機数取得
	inline int GetLives() {
		return lives;
	}

	//移動前の位置に戻す
	inline void MoveReset() {
		setPosition(oldPos);
	}

	//線の開始・終了位置を取得
	inline void GetLinePos(VECTOR* startPos, VECTOR* endPos) {
		*startPos = this->startPos;
		*endPos = this->endPos;
	}
private:
	const float SPEED = 1.2f;		//移動速度
	const float JUMPPOWER = 1.2f;	//ジャンプ力
	const float GRAVITY = 0.15f;		//重力

	VECTOR oldPos;	//移動前の位置
	float accel;	//加速度
	int lives;		//残機数
	int hp;			//体力
	int maxHp;		//体力の最大値
	int deadCnt;	//死亡時のｶｳﾝﾄ
	bool isDead;	//死亡ﾌﾗｸﾞ

	Sprite* livesIcon;	//残機数表示用
	Sprite* hpGauge;	//体力ゲージ

	
	VECTOR startPos, endPos;	//線の開始位置と終了位置
};