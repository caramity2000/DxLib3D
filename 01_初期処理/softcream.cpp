#include "softcream.h"

Softcream::Softcream() {

	loadModel("model/顔につける用ソフトクリームver1_01/ソフトクリーム(単体).pmx");	//ﾓﾃﾞﾙの読み込み
	setPosition(VGet(10.0f, 0, 0));	//座標の設定
	setRotation(VGet(0, ToRadian(90), 0));	//回転の設定
	setScale(9.0f);
	setupCollInfo();//衝突判定の設定

}	//ｺﾝｽﾄﾗｸﾀ

//ﾃﾞｽﾄﾗｸﾀ
Softcream::~Softcream() {

}


//初期化処理
void Softcream::Init() {
}

//更新処理
void Softcream::Update() {
	
}

//表示処理
void Softcream::Draw() {
	drawModel();
}