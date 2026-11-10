#include "sprite.h"

// ｺﾝｽﾄﾗｸﾀ
Sprite::Sprite() : 
	pos(VGet(0, 0, 0)),index(0),angle(0)
{
	//pos = VGet(0,0,0);
	//index = 0;
	//angle = 0;
}
// ﾃﾞｽﾄﾗｸﾀ
Sprite::~Sprite()
{
}

// 画像読込み
bool Sprite::loadSprite(const char* fileName)
{
	GHandle = LoadGraph(fileName);
	if (GHandle == -1)
	{
		ErrMsg("画像の読込み失敗", fileName);
		return false;	//失敗
	}
	return true;	//成功
}
// 画像の分割読込み(ｵｰﾊﾞｰﾛｰﾄﾞ関数)
bool Sprite::loadSprite(const char* fileName,
	int xnum, int ynum, int w, int h)
{
	// 画像枚数分の領域獲得
	SHandle = new int[xnum * ynum];

	int rtn = LoadDivGraph(
		fileName,		// ﾌｧｲﾙ名
		xnum * ynum,	// 総画像数
		xnum,			// 横の画像数
		ynum,			// 縦の画像数
		w, h,			// 画像1枚のｻｲｽﾞ
		SHandle);		// 画像ﾊﾝﾄﾞﾙ(配列)
	if (rtn == -1)
	{
		ErrMsg("画像の読込み失敗", fileName);
		return false;	// 失敗
	}
	return true;	// 成功
}

// 画像のビルボード表示(1枚画像用)
void Sprite::drawBillboard(VECTOR pos, 
	float size, float angle)
{
	DrawBillboard3D(
		pos,		//表示位置
		0.5f, 0.5f,	//画像の中心位置(UV座標)
		size,		//表示するｻｲｽﾞ
		angle,		//表示する角度
		GHandle,	//画像ﾊﾝﾄﾞﾙ
		TRUE);		//透明度(TRUE:有効)
}
// 画像のビルボード表示(分割画像用:ｵｰﾊﾞｰﾛｰﾄﾞ関数)
void Sprite::drawBillboard(VECTOR pos, 
	float size, float angle, int index)
{
	DrawBillboard3D(
		pos,		//表示位置
		0.5f, 0.5f,	//画像の中心位置(UV座標)
		size,		//表示するｻｲｽﾞ
		angle,		//表示する角度
		SHandle[index],	//画像ﾊﾝﾄﾞﾙ
		TRUE);		//透明度(TRUE:有効)
}



//画像ハンドルの解放(1枚画像用)
void Sprite::deleteSprite()
{
	DeleteGraph(GHandle);
}
//画像ハンドルの解放(分割画像用)
void Sprite::deleteDivSprite()
{
	delete[] SHandle;
}

// 画像の2D表示
// isTrans:true[透過有効]
void Sprite::drawGraph(int x, int y, bool isTrans)
{
	DrawGraph(x, y, GHandle, isTrans);
}

//画像の2D表示（分割画像用:オーバーロード関数）
void Sprite::drawGraph(int x, int y, int index, bool isTrans) {

	DrawGraph(x, y, SHandle[index], isTrans);
}

//画像の拡大縮小表示
void Sprite::drawExtGraph(RECT rect, int index, bool isTrans) {

	DrawExtendGraph(
		rect.left,rect.top,			//左上の座標
		rect.right,rect.bottom,		//右下の座標
		SHandle[index], isTrans);
}

// 半透明を有効にする
// alpha：透明度（0[完全透明] ～ 255[完全不透明]）
void Sprite::alphaOn(int alpha)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
}
// 半透明を無効にする
void Sprite::alphaOff()
{
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}


//画像のビルボード表示（1枚画像用、矩形指定）
void Sprite::drawModiBillboard(VECTOR pos, RECT rect) {

	DrawModiBillboard3D(
		pos,						//表示位置
		rect.left, rect.top,		//左上
		rect.right, rect.top,		//右上
		rect.right, rect.bottom,	//右下
		rect.left, rect.bottom,		//左下
		GHandle,					//画像ハンドル
		TRUE);						//TRUE:透過する
}
//画像のビルボード表示（分割画像用、矩形指定;オーバーロード関数）
void Sprite::drawModiBillboard(VECTOR pos, RECT rect,int index) {

	DrawModiBillboard3D(
		pos,						//表示位置
		rect.left, rect.top,		//左上
		rect.right, rect.top,		//右上
		rect.right, rect.bottom,	//右下
		rect.left, rect.bottom,		//左下
		SHandle[index],					//画像ハンドル
		TRUE);
}