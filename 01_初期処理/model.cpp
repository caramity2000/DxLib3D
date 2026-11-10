#include "model.h"

// ｺﾝｽﾄﾗｸﾀ
Model::Model() :
	pos(VGet(0,0,0)), rot(VGet(0,0,0)), 
	scale(1.0f),radius(0),dir(DIRECTION::UP)
{
	//pos = VGet(0, 0, 0);
	//rot = VGet(0, 0, 0);
	//scale = 1.0f;
	//radius = 0;
	//dir=DIRECTION::UP;
}
// ﾃﾞｽﾄﾗｸﾀ
Model::~Model()
{
	MV1DeleteModel(MHandle);	//ﾓﾃﾞﾙﾊﾝﾄﾞﾙの削除
}

// モデル読込み
bool Model::loadModel(const char* fileName)
{
	// モデルの読込み
	MHandle = MV1LoadModel(fileName);
	if (MHandle == -1)
	{
		ErrMsg("モデルの読込み失敗", fileName);
		return false;
	}
	return true;
}

// モデル表示
void Model::drawModel()
{
	MV1DrawModel(MHandle);
}

//コリジョン（当たり判定）情報を設定する
void Model::setupCollInfo() {

	MV1SetupCollInfo(
		MHandle,	//ﾓﾃﾞﾙﾊﾝﾄﾞﾙ
		-1,			//ｺﾘｼﾞｮﾝ情報を設定するﾌﾚｰﾑの番号(-1:全体)
		8, 8, 8);	//X,Y,Z方向の空間分割数
}

// Sphere(球)の表示
void Model::drawSphere(VECTOR pos, float radius, bool fill)
{
	DrawSphere3D(
		pos,	//表示位置
		radius,	//半径
		8,		//分割数
		GetColor(255, 0, 0),	//ﾃﾞｨﾌｭｰｽﾞ(物体の色)色
		GetColor(255, 0, 0),	//ｽﾍﾟｷｭﾗｰ(反射した色)色
		fill);	//TRUE:塗りつぶし FALSE:ﾌﾚｰﾑ表示
}

//Capsule（カプセル）の表示
void Model::drawCapsule(VECTOR pos1, VECTOR pos2, float radius, bool fill) {

	DrawCapsule3D(
		pos1,		//カプセルの上の位置
		pos2,		//カプセルの下の位置
		radius,		//半径
		8,			//分割数
		GetColor(0, 128, 255),	//ﾃﾞｨﾌｭｰｽﾞ(物体の色)色
		GetColor(0, 128, 255),	//ｽﾍﾟｷｭﾗｰ(反射した色)色
		fill);		//TRUE:塗りつぶし FALSE:ﾌﾚｰﾑ表示
}
//Line（線）の表示
void Model::drawLine(VECTOR startpos, VECTOR endpos) {
		DrawLine3D(
		startpos,	//線の始点
		endpos,		//線の終点
		GetColor(255, 255, 255));	//線の色(白)
}
