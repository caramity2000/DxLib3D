#include "player.h"

//ｺﾝｽﾄﾗｸﾀ
Player::Player()
{
	loadModel("model/reimu216_140107/博麗霊夢216.pmd");	//モデルの読み込み
	setScale(1.0f);
	radius = 1.5f;	//半径
	livesIcon = new Sprite;
	livesIcon->loadSprite("sprite/images_dog.png");
	hpGauge = new Sprite;
	hpGauge->loadSprite("sprite/hpGauge.png", 1, 2, 128, 32);

	//オーバーロード　　同じ名前の関数だが、引数の数が違う
}
//ﾃﾞｽﾄﾗｸﾀ
Player::~Player()
{
	delete livesIcon;
	delete hpGauge;
}

//初期化処理
void Player::Init()
{
	pos = VGet(0, 0, 0);
	rot = VGet(0, 0, 0);
	isDead = false;
	accel = 0;
	lives = 3;		//残機数
	hp = maxHp = 128;		//体力
	dir = DIRECTION::UP;	//奥向き
}
//更新処理
void Player::Update()
{
	oldPos = pos;//移動前の位置を退避	//Dir4Move();	//4方向移動
	Dir8Move();		//8方向移動
}
//表示処理
void Player::Draw()
{
	setPosition(pos);
	//setRotation(VGet(0, ToRadian(static_cast<float>(dir) * 90.0f), 0));
	setRotation(rot);
	drawModel();

	//残機数表示
	for (int i = 0; i < lives-1; i++) {

		livesIcon->drawGraph(i * 75+10, 600, TRUE);
	}

	//HPゲージ表示
	int gaugeLeft, gaugeTop, extSize;	//左、上、縮小サイズ
	gaugeLeft = 10;	//左
	gaugeTop = 50;	//上
	hpGauge->drawGraph(gaugeLeft, gaugeTop, 0, FALSE);	//赤ゲージ

	extSize = hp;	//緑ゲージのサイズを算出
	RECT rect{ gaugeLeft ,gaugeTop ,gaugeLeft + extSize ,gaugeTop + 32 };  //初期化と変数設定を同時にしている
	//RECT rect;
	//rect.left = gaugeLeft;				//左
	//rect.top = gaugeTop;				//上
	//rect.right = gaugeLeft + extSize;	//右
	//rect.bottom = gaugeTop + 32;		//下
	hpGauge->drawExtGraph(rect, 1, FALSE);	//緑ゲージ

	// 当たり判定の確認用
	//VECTOR p = pos;
	//p.y += 2.5f;	//高さを上げる
	//drawSphere(p, radius, FALSE);
	VECTOR pos1, pos2;
	pos1 = pos2 = pos;	//プレイヤーの位置をコピー
	pos1.y += 10.5f;	//上半球の中心座標
	pos2.y += 3.0f;	//下半球の中心座標

	//drawCapsule(pos1, pos2, radius, FALSE);

	//プレイヤーの前後に線を表示
	
	//startPos = endPos = pos;	//プレイヤーの位置
	//startPos.y += 10.5f;	startPos.z += 20.0f;	//開始位置
	//endPos.y += 10.5f;		endPos.z -= 20.0f;		//終了位置

	MATRIX mat1;			//４x４行列
	VECTOR rayPos = pos;	//プレイヤーの位置

	mat1=MGetRotY(rot.y);	//Y軸回転行列を作成
	VECTOR axisZ = VGet(0, 0, 1.0f);	//軸ベクトル
	axisZ = VTransform(axisZ, mat1);	//軸ベクトルを回転行列で変換

	startPos = endPos = VScale(axisZ, 20.0f);	//線の長さ

	startPos =rayPos;	//開始位置加算
	endPos = VSub(rayPos, endPos);		//終了位置減算
	startPos.y += 10.5f;	endPos.y += 10.5f;	//Y座標を上げる

	drawLine(startPos, endPos);		//線の表示

	//プレイヤーの縦に線を表示
	VECTOR topPos, bottomPos;
	topPos = VGet(pos.x, pos.y + 15.0f, pos.z);
	bottomPos = VGet(pos.x, pos.y - 15.0f, pos.z);
	drawLine(topPos, bottomPos);		
}


// ﾀｲﾄﾙ画面用
void Player::DrawTitle()
{
	setPosition(VGet(0,0,-80.0f));
	rot.y += 0.01f;		//Y軸回転
	setRotation(rot);
	drawModel();


}

// ｹﾞｰﾑｵｰﾊﾞｰ画面用
void Player::DrawOver()
{
	setPosition(VGet(0, 1.5f, -70.0f));	
	rot.y = 0;				//Y軸回転
	if(rot.z < ToRadian(90))
		rot.z += 0.02f;
	//rot.z = ToRadian(90);	//Z軸回転
	setRotation(rot);
	drawModel();
}

//クリア画面用
void Player::DrawClear() {

	
	setPosition(pos);
	if(CheckHitKey(KEY_INPUT_SPACE)==1)
	rot.y += 0.55f;		//Y軸回転
	setRotation(rot);
	drawModel();

	// 自由落下の法則:　y = 1/2gt^2  g=重力 , t=時間
	// 鉛直投げ上げ	 :  y = v0t - 1/2gt^2
	pos.y += JUMPPOWER - accel;
	accel += GRAVITY;

	if (pos.y <= 0) {//地面の下まで降りた時に

		accel = 0;	//地面に調整
		pos.y = 0;	//加速度初期化
	}
}

//死亡時のｶｳﾝﾄ処理
bool Player::GetDeadCnt()
{
	deadCnt--;
	if (deadCnt <= 0) {
		isDead = false;
		return true;
	}
	return false;
}

// 死亡ﾌﾗｸﾞの設定
void Player::SetIsDead(int deadCnt)
{
	isDead = true;
	this->deadCnt = deadCnt;
}

//残機数を減らす
void Player::TakeDamage() {

	lives--;
}

//体力を減らす
void Player::TakeDamage(int damage) {
	hp -= damage;
}

//4方向移動
void Player::Dir4Move() {

	if (CheckHitKey(KEY_INPUT_W) == 1) {
		pos.z += SPEED;
		dir = DIRECTION::UP;	//奥向き
	}
	else if (CheckHitKey(KEY_INPUT_A) == 1)
	{
		pos.x -= SPEED;
		dir = DIRECTION::LEFT;	//左向き

	}
	else if (CheckHitKey(KEY_INPUT_S) == 1) {
		pos.z -= SPEED;
		dir = DIRECTION::DOWN;	//下向き
	}

	else if (CheckHitKey(KEY_INPUT_D) == 1) {
		pos.x += SPEED;
		dir = DIRECTION::RIGHT;	//右向き
	}
	//プレイヤーの向き(角度)を設定
	rot.y = ToRadian(static_cast<float>(dir) * 90.0f);
}

//8方向移動
void Player::Dir8Move() {

	//入力キーの配列
	bool isKey[4] = { false,false,false,false };

	if (CheckHitKey(KEY_INPUT_W) == 1) {
		isKey[static_cast<int>(DIRECTION::UP)] = true;
	}
	if (CheckHitKey(KEY_INPUT_A) == 1) {
		isKey[static_cast<int>(DIRECTION::LEFT)] = true;
	}
	if (CheckHitKey(KEY_INPUT_S) == 1) {
		isKey[static_cast<int>(DIRECTION::DOWN)] = true;
	}
	if (CheckHitKey(KEY_INPUT_D) == 1) {
		isKey[static_cast<int>(DIRECTION::RIGHT)] = true;
	}

	//斜めの移動速度
	float speed = SPEED / ROOT2;

	//入力キー毎の角度（８方向）
	if (isKey[static_cast<int>(DIRECTION::DOWN)] &&
		isKey[static_cast<int>(DIRECTION::LEFT)])	//左下
	{
		rot.y = ToRadian(45);	//45度(真下（DOWN）が0度)
		pos.x -= speed;
		pos.z -= speed;
		dir = DIRECTION::LEFTDOWN;	
	}
	else if (isKey[static_cast<int>(DIRECTION::UP)] &&
		isKey[static_cast<int>(DIRECTION::LEFT)])	//左上
	{
		rot.y = ToRadian(135);
		pos.x -= speed;
		pos.z += speed;
		dir = DIRECTION::LEFTUP;
	}
	else if (isKey[static_cast<int>(DIRECTION::UP)] &&
		isKey[static_cast<int>(DIRECTION::RIGHT)])	//右上
	{
		rot.y = ToRadian(225);
		pos.x += speed;
		pos.z += speed;
		dir = DIRECTION::RIGHTUP;
	}
	else if (isKey[static_cast<int>(DIRECTION::DOWN)] &&
		isKey[static_cast<int>(DIRECTION::RIGHT)])	//右下

	{
		rot.y = ToRadian(315);
		pos.x += speed;
		pos.z -= speed;
		dir = DIRECTION::RIGHTDOWN;
	}
	else if (isKey[static_cast<int>(DIRECTION::DOWN)]){//下

		rot.y = 0;
		pos.z -= SPEED;
		dir = DIRECTION::DOWN;
		}
	else if (isKey[static_cast<int>(DIRECTION::LEFT)]) {//左

		rot.y = ToRadian(90);
		pos.x -= SPEED;
		dir = DIRECTION::LEFT;
	}
	else if (isKey[static_cast<int>(DIRECTION::UP)]) {//上

		rot.y = ToRadian(180);
		pos.z += SPEED;
		dir = DIRECTION::UP;
	}
	else if (isKey[static_cast<int>(DIRECTION::RIGHT)]) {//右

		rot.y = ToRadian(270);
		pos.x += SPEED;
		dir = DIRECTION::RIGHT;
	}
}

