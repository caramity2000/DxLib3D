#include "explosion.h"

//ｺﾝｽﾄﾗｸﾀ
Explosion::Explosion()
{
	loadSprite("sprite/爆発.png", 8, 2, 96, 96);
}
//ﾃﾞｽﾄﾗｸﾀ
Explosion::~Explosion()
{
	deleteDivSprite();	//画像ﾊﾝﾄﾞﾙの破棄
}

//初期化処理
void Explosion::Init()
{
	pos = VGet(0, -50.0f, 0);	//地面の下に隠す
	index = 0;
	angle = 0;
}
//更新処理
void Explosion::Update()
{
}
//表示処理
void Explosion::Draw()
{
	if (pos.y >= 0)	//地上に出ている時
	{
		drawBillboard(pos, 100.0f, angle, index);
		index++;
		if (index >= 16) {
			Init();		//最後の画像まで来たら初期化
		}
	}
}
