#pragma once
#include "common.h"

#define TEXTCOLOR GetColor(255,255,0)	//文字色(黄)

// テキストクラス
class Text
{
public:
	Text();		//ｺﾝｽﾄﾗｸﾀ
	~Text();	//ﾃﾞｽﾄﾗｸﾀ

	// 文字フォントのサイズ設定
	void setFontSize(int size);

	// 文字色の設定
	void setTextColor(int red, int green, int blue);

	// 文字フォントの変更
	void changeFont(const char* fontName);

	// テキストの表示
	void drawString(int x, int y, const char* text);

	// フォントの組み込み
	bool addFont(const char* fontPath);

	// フォントの削除
	void removeFont();

private:

	char fontPath[128];		//ﾌｫﾝﾄﾊﾟｽ
	unsigned int textColor;	//文字色
};