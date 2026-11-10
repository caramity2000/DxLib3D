#pragma once
#include "model.h"
#include "sound.h"
#include "sprite.h"

// ステージクラス(ﾓﾃﾞﾙｸﾗｽとｻｳﾝﾄﾞｸﾗｽを継承)
class Stage : public Model,public Sound
{
public:
	Stage();	//ｺﾝｽﾄﾗｸﾀ
	~Stage();	//ﾃﾞｽﾄﾗｸﾀ

	void Init();	//初期化処理
	void Update();	//更新処理
	void Draw();	//表示処理

	// 現在のシーン(場面)を取得
	inline SCENE getScene() {
		return scene;
	}
	// シーンを設定
	inline void setScene(SCENE scene)
	{
		this->scene = scene;	//次のｼｰﾝへ
		Init();
	}

private:

	SCENE	scene;	// 場面
	Sprite* title;	// ｹﾞｰﾑﾀｲﾄﾙ
	Sprite* push;	// ｽﾀｰﾄｷｰ

	Sprite* over;	// ｹﾞｰﾑｵｰﾊﾞｰ
	Sprite* clear;	// ｹﾞｰﾑｸﾘｱ
	Sprite* toTitle;// ﾀｲﾄﾙに戻る

	int alpha;		// 透明度(0～255)
	int addAlpha;	// 透明度の加減算用
};