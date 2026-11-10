#pragma once
#include "common.h"
#include <cmath>	//数学関数用

//モデルクラス
class Model
{
public:
	Model();	// ｺﾝｽﾄﾗｸﾀ
	~Model();	// ﾃﾞｽﾄﾗｸﾀ

	// モデル読込み
	bool loadModel(const char* fileName);

	// モデル表示
	void drawModel();

	//コリジョン（当たり判定）情報を設定する
	void setupCollInfo();

	// === 基本図形 ===
	// Sphere(球)の表示
	void drawSphere(VECTOR pos, float radius, bool fill);

	//Capsule（カプセル）の表示
	void drawCapsule(VECTOR pos1, VECTOR pos2, float radius, bool fill);

	//Line（線）の表示
	void drawLine(VECTOR startpos, VECTOR endpos );


	//モデルハンドルの取得
	inline int getMHandle() {

		return MHandle;
	}

	// 位置の設定
	inline void setPosition(VECTOR pos)
	{
		this->pos = pos;
		MV1SetPosition(MHandle, this->pos);
	}
	// 回転の設定
	inline void setRotation(VECTOR rot)
	{
		this->rot = rot;
		MV1SetRotationXYZ(MHandle, this->rot);
	}
	// 拡大縮小の設定
	inline void setScale(float scale)
	{
		this->scale = scale;
		MV1SetScale(MHandle, VGet(this->scale, this->scale, this->scale));
	}

	// 位置の取得
	inline VECTOR getPosition()
	{
		return pos;
	}
	// 半径の取得
	inline float getRadius() 
	{
		return radius;
	}
	//向きの取得
	inline DIRECTION getDirection() {
		return dir;
	}

private:
	int MHandle;	//ﾓﾃﾞﾙﾊﾝﾄﾞﾙ

protected:	//継承先のみ使用可能

	VECTOR pos;		//位置
	VECTOR rot;		//回転
	float scale;	//拡大縮小
	float radius;	//半径
	DIRECTION dir;	//方向
};