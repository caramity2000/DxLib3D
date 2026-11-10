#pragma once
#include "common.h"

// スプライト(画像)クラス
class Sprite
{
public:
	Sprite();	// ｺﾝｽﾄﾗｸﾀ
	~Sprite();	// ﾃﾞｽﾄﾗｸﾀ

	// 画像読込み
	bool loadSprite(const char* fileName);
	// 画像の分割読込み(ｵｰﾊﾞｰﾛｰﾄﾞ関数)
	bool loadSprite(const char* fileName,
		int xnum, int ynum, int w, int h);

	// 画像の2D表示(1枚画像用)
	void drawGraph(int x, int y, bool isTrans);
	//画像の2D表示（分割画像用:オーバーロード関数）
	void drawGraph(int x, int y, int index, bool isTrans);

	//画像の拡大縮小表示
	void drawExtGraph(RECT rect, int index, bool isTrans);

	// 画像のビルボード表示(1枚画像用)
	void drawBillboard(VECTOR pos, float size, float angle);
	// 画像のビルボード表示(分割画像用:ｵｰﾊﾞｰﾛｰﾄﾞ関数)
	void drawBillboard(VECTOR pos, float size, float angle,int index);

	//画像のビルボード表示（1枚画像用、矩形指定）
	void drawModiBillboard(VECTOR pos, RECT rect);
	//画像のビルボード表示（分割画像用、矩形指定;オーバーロード関数）
	void drawModiBillboard(VECTOR pos, RECT rect,int index);


	// 画像ハンドルの解放
	void deleteSprite();	//1枚画像用
	void deleteDivSprite();	//分割画像用

	// 半透明を有効にする
	void alphaOn(int alpha);
	// 半透明を無効にする
	void alphaOff();

	// 位置の設定
	inline void setPosition(VECTOR pos)
	{
		this->pos = pos;
	}

private:
	int GHandle;	// 画像ﾊﾝﾄﾞﾙ(1枚画像用)
	int* SHandle;	// 画像ﾊﾝﾄﾞﾙ(分割画像用)

protected:
	VECTOR pos;		// 表示位置
	int index;		// 分割画像の配列番号
	float angle;	// 角度
};