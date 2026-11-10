#pragma once
#include "model.h"
#include "sprite.h"

//ソフトクリームクラス(ﾓﾃﾞﾙｸﾗｽを継承)
class Softcream : public Model
{
public:
	Softcream();	//ｺﾝｽﾄﾗｸﾀ
	~Softcream();	//ﾃﾞｽﾄﾗｸﾀ

	void Init();	//初期化処理
	void Update();	//更新処理
	void Draw();	//表示処理

private:

};