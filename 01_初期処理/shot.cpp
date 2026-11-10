#include "shot.h"


// ｺﾝｽﾄﾗｸﾀ
Shot::Shot()
{
	radius = 1.4f;	//弾の半径

	shotSE = new Sound;	//弾撃つ音
	shotSE->loadSound("sound/maou_se_battle_gun02.mp3");
	shotSE->changeVolume(192);
}
// ﾃﾞｽﾄﾗｸﾀ
Shot::~Shot()
{
	delete shotSE;
}

// 初期化処理
void Shot::Init()
{
	for (int i = 0; i < SHOTMAX; i++)
	{
		shotPos[i] = VGet(0, -100.0f, 0);//地面の下に隠す
		isShot[i] = false;		//未発射
		dir[i] = DIRECTION::UP;	//奥向き
	}
	interval = 0;
}

//初期化処理(ｵｰﾊﾞｰﾛｰﾄﾞ関数)
void Shot::Init(int index)
{
	shotPos[index] = VGet(0, -100.0f, 0);//地面の下に隠す
	isShot[index] = false;		//未発射
	dir[index] = DIRECTION::UP;	//奥向き
}

// 更新処理
void Shot::Update()
{
	// 弾の発射キー
	if (interval <= 0 && CheckHitKey(KEY_INPUT_SPACE) == 1)
	{
		for (int i=0; i<SHOTMAX; i++)
		{
			if (isShot[i]) continue;// 発射中ならば飛ばす(Skip)

			playerPos.y += 2.0f;	// 弾の高さを調整
			shotPos[i] = playerPos;	// ﾌﾟﾚｲﾔｰの位置を設定
			dir[i] = playerDir;		//ﾌﾟﾚｲﾔｰの向きを設定
			isShot[i] = true;		// 発射中にする
			interval = 3;			// 弾の間隔

			shotSE->playSound(FALSE);	//弾撃つ音

			break;					// 一発撃ったらbreak;
		}
	}
	if (interval > 0)interval--;	// 次の弾までのｶｳﾝﾄﾀﾞｳﾝ

	// 弾の移動
	for (int i = 0; i < SHOTMAX; i++)
	{
		if (!isShot[i])	continue;	//発射中でなければ飛ばす

		//Dir4Shot(i);	//4方向射撃
		Dir8Shot(i);	//8方向射撃

		if (fabs(shotPos[i].z) > 200.0f || fabs(shotPos[i].x) > 200.0f) {
			Init(i);	//弾を初期化
		}

	}
}
// 表示処理
void Shot::Draw()
{
	for (int i = 0; i < SHOTMAX; i++)
	{
		if (!isShot[i]) continue;//未発射ならば飛ばす(Skip)

		drawSphere(shotPos[i], radius, TRUE);
	}
}

//4方向射撃
void Shot::Dir4Shot(int index) {

	switch (dir[index])
	{
	case DIRECTION::UP:	//奥
		shotPos[index].z += SPEED;
		break;
	case DIRECTION::LEFT:	//左
		shotPos[index].x -= SPEED;
		break;
	case DIRECTION::DOWN:	//手前
		shotPos[index].z -= SPEED;
		break;
	case DIRECTION::RIGHT:	//右
		shotPos[index].x += SPEED;
		break;
	}
}

//8方向射撃
void Shot::Dir8Shot(int index) {

	float speed = SPEED / ROOT2;
	switch (dir[index])
	{
	case DIRECTION::DOWN:
	case DIRECTION::LEFT:
	case DIRECTION::UP:
	case DIRECTION::RIGHT:
		//4方向の時
		Dir4Shot(index);
		break;

	case DIRECTION::LEFTDOWN:	//左下
		shotPos[index].x -= speed;
		shotPos[index].z -= speed;
		break;

	case DIRECTION::LEFTUP:		//左上
		shotPos[index].x -= speed;
		shotPos[index].z += speed;
		break;

	case DIRECTION::RIGHTUP:	//右上
		shotPos[index].x += speed;
		shotPos[index].z += speed;
		break;

	case DIRECTION::RIGHTDOWN:	//右下
		shotPos[index].x += speed;
		shotPos[index].z -= speed;
		break;

	}
}
