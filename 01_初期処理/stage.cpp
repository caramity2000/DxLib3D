#include "stage.h"

//ｺﾝｽﾄﾗｸﾀ
Stage::Stage() :
	scene(SCENE::TITLE), alpha(255), addAlpha(-2)
{
	//loadModel("model/stage.mqo");
	loadModel("model/stage_flat.mqo");
	setPosition(VGet(0, 0, 0));
	setScale(1.33f);
	setupCollInfo();	//コリジョン設定
	//scene = SCENE::TITLE;
	//alpha = 255;
	//addAlpha = -2;

	clear = nullptr;
}
//ﾃﾞｽﾄﾗｸﾀ
Stage::~Stage()
{
	stopSound();
}

//初期化処理
void Stage::Init()
{
	switch (scene)
	{
	case SCENE::TITLE:	//ﾀｲﾄﾙ画面
		

		// ｹﾞｰﾑﾀｲﾄﾙ画像読込み
		title = new Sprite;
		title->loadSprite("sprite/title.png");
		push = new Sprite;
		push->loadSprite("sprite/push.png");

		break;

	case SCENE::GAME:	//ｹﾞｰﾑ中
		
		

		loadSound("sound/uchunohajimari.mp3");
		changeVolume(192);
		playSound(TRUE);
		break;

	case SCENE::OVER:	//ｹﾞｰﾑｵｰﾊﾞｰ画面
		over = new Sprite;
		over->loadSprite("sprite/over.png");		//ｹﾞｰﾑｵｰﾊﾞｰ画像
		toTitle = new Sprite;
		toTitle->loadSprite("sprite/toTitle.png");	//ﾀｲﾄﾙに戻る画像

		break;

	case SCENE::CLEAR:	//ｹﾞｰﾑｸﾘｱ画面
		clear = new Sprite;
		clear->loadSprite("sprite/clear.png");		//ｹﾞｰﾑｸﾘｱ画像
		toTitle = new Sprite;
		toTitle->loadSprite("sprite/toTitle.png");	//ﾀｲﾄﾙに戻る画像
		break;
	}

}
//更新処理
void Stage::Update()
{
	// エンターキーの入力
	if (CheckHitKey(KEY_INPUT_RETURN) == 1)
	{
		switch (scene)
		{
		case SCENE::TITLE:	//ﾀｲﾄﾙ画面
			delete title;
			delete push;

			scene = SCENE::GAME;	//ｹﾞｰﾑ中へ
			break;

		case SCENE::OVER:	//ｹﾞｰﾑｵｰﾊﾞｰ
			delete over;
			scene = SCENE::TITLE;	//ﾀｲﾄﾙ画面へ
			
		case SCENE::CLEAR:	//ｹﾞｰﾑｸﾘｱ
			if(clear != nullptr)delete clear;
			delete toTitle;

			scene = SCENE::TITLE;	//ﾀｲﾄﾙ画面へ
			break;
		}
		Init();
		
		//入力が解除されるまで繰り返し
		while (CheckHitKey(KEY_INPUT_RETURN) == 1);
	}

}
//表示処理
void Stage::Draw()
{
	drawModel();	// ｽﾃｰｼﾞ表示

	switch (scene)
	{
	case SCENE::TITLE:	// ﾀｲﾄﾙ画面
		
		title->drawGraph(
			WND_W / 2 - 1154 / 2, 200, TRUE);

		push->alphaOn(alpha);	//透明度ON
		push->drawGraph(
			WND_W / 2 - 954 / 2, 370, TRUE);
		push->alphaOff();		//透明度OFF

		//alpha -= 2;	// 徐々に透明度を上げる
		//// 完全透明になったら完全不透明に戻す
		//if (alpha <= 0) alpha = 255;

		alpha += addAlpha;	//徐々に透明度を変更
		if (alpha <= 0) addAlpha = 2;	//完全透明→完全不透明
		if (alpha >= 255) addAlpha = -2;//完全不透明→完全透明

		SetFogEnable(TRUE);	//フォグ（霧）を有効にする
		SetFogColor(255, 255, 255);	//フォグの色を設定（灰）
		SetFogStartEnd(100, 400);	//フォグの開始・終了位置を設定

		break;

	case SCENE::GAME:	//ｹﾞｰﾑ中
		break;
	case SCENE::OVER:	//ｹﾞｰﾑｵｰﾊﾞｰ画面

		over->drawGraph(
			WND_W / 2 - 800 / 2, 200, TRUE);

		toTitle->alphaOn(alpha);	//透明度ON
		toTitle->drawGraph(
			WND_W / 2 - 800 / 2, 370, TRUE);
		toTitle->alphaOff();		//透明度OFF

		alpha += addAlpha;	//徐々に透明度を変更
		if (alpha <= 0) addAlpha = 6;	//完全透明→完全不透明
		if (alpha >= 255) addAlpha = -6;//完全不透明→完全透明

		break;
	case SCENE::CLEAR:	//ｹﾞｰﾑｸﾘｱ画面

		clear->drawGraph(
			WND_W / 2 - 800 / 2, 200, TRUE);

		toTitle->alphaOn(alpha);	//透明度ON
		toTitle->drawGraph(
			WND_W / 2 - 800 / 2, 370, TRUE);
		toTitle->alphaOff();		//透明度OFF

		alpha += addAlpha;	//徐々に透明度を変更
		if (alpha <= 0) addAlpha = 2;	//完全透明→完全不透明
		if (alpha >= 255) addAlpha = -2;//完全不透明→完全透明
		break;
	}
}
