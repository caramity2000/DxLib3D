#include "text.h"

//ｺﾝｽﾄﾗｸﾀ
Text::Text()
{
	textColor = TEXTCOLOR;
}
//ﾃﾞｽﾄﾗｸﾀ
Text::~Text()
{
}

// 文字フォントのサイズ設定
void Text::setFontSize(int size)
{
	SetFontSize(size);
}

// 文字色の設定
void Text::setTextColor(int red, int green, int blue)
{
	textColor = GetColor(red, green, blue);
}

// 文字フォントの変更
void Text::changeFont(const char* fontName)
{
	if (ChangeFont(fontName) == -1)
	{
		ErrMsg("フォントの変更に失敗", fontName);
	}
}

// テキストの表示
void Text::drawString(int x, int y, const char* text)
{
	DrawFormatString(x, y, textColor, text);
}

// フォントの組み込み
bool Text::addFont(const char* fontPath)
{
	strcpy_s(this->fontPath, fontPath);

	if (AddFontResourceEx(
		fontPath,		//ﾌｫﾝﾄﾊﾟｽ
		FR_PRIVATE,		//終了時に削除
		NULL) == NULL)
	{
		ErrMsg("文字フォントの組み込みに失敗", fontPath);
		return false;
	}
	return true;
}

// フォントの削除
void Text::removeFont()
{
	RemoveFontResource(fontPath);
}
