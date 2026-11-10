#pragma once
#include "sprite.h"

// 爆発クラス(Spriteｸﾗｽを継承)
class Explosion : public Sprite
{
public:
	Explosion();	//ｺﾝｽﾄﾗｸﾀ
	~Explosion();	//ﾃﾞｽﾄﾗｸﾀ

	void Init();	//初期化処理
	void Update();	//更新処理
	void Draw();	//表示処理

};