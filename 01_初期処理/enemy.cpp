#include "enemy.h"

// コンストラクタ
Enemy::Enemy()
{
	loadModel("model/kurage07/kurage07/kurage-07.pmx");	//モデルの読み込み
	setScale(0.8f);	//拡大縮小
	radius = 5.0f;	//半径
	hpGauge = new Sprite;
	hpGauge->loadSprite("sprite/hpGauge.png", 1, 2, 128, 32);
}
// デストラクタ
Enemy::~Enemy()
{
	delete hpGauge;
}

// 初期化処理
void Enemy::Init()
{
	maxHp = 5;
	for (int i = 0; i < ENEMYMAX; i++)
	{
		initPosition(i);
	}
}

// 初期化処理(ｵｰﾊﾞｰﾛｰﾄﾞ関数)
void Enemy::Init(int index)
{
	initPosition(index);
	//float x = GetRand(100) - 50;//-50～50の乱数
	//float z = GetRand(100) + 150;
	//enemyPos[index] = VGet(x, 0, z);
	//isDead[index] = false;
	////hp[index] = maxHp;
}

// 更新処理
void Enemy::Update()
{
	for (int i = 0; i < ENEMYMAX; i++)
	{
		if (isDead[i])continue;//死亡中は飛ばす(Skip)

		//プレイヤーの位置と敵の位置から角度（ﾗｼﾞｱﾝ）を決める
		float angle;
		angle = atan2(playerPos.z - enemyPos[i].z,
					  playerPos.x - enemyPos[i].x);

		//角度と移動速度から座標に加算する値を計算する
		enemyPos[i].x += SPEED * cos(angle);
		enemyPos[i].z += SPEED * sin(angle);
		fYaw[i] = -angle - ToRadian(90);

		//switch (dir[i])
		//{
		//case DIRECTION::DOWN:
		//	enemyPos[i].z -= SPEED;
		//	break;
		//case DIRECTION::LEFT:
		//	enemyPos[i].x -= SPEED;
		//	break;
		//case DIRECTION::UP:
		//	enemyPos[i].z += SPEED;
		//	break;
		//case DIRECTION::RIGHT:
		//	enemyPos[i].x += SPEED;
		//	
		//	break;
		//}
		//
		////画面外に出たら初期化
		//if (fabs(enemyPos[i].z) >250|| fabs(enemyPos[i].x)>250)
		//{
		//	Init(i);	//敵を初期化
		//}
	}
}
// 表示処理
void Enemy::Draw()
{
	for (int i = 0; i < ENEMYMAX; i++)
	{
		if (isDead[i])continue;//死亡中は飛ばす(Skip)

		setPosition(enemyPos[i]);	// 位置の設定
		setRotation(VGet(0, fYaw[i],0));
		drawModel();		// ﾓﾃﾞﾙの表示

		// 当たり判定の確認用
		VECTOR p = enemyPos[i];
		p.y += 7.0f;	//高さを上げる
		drawSphere(p, radius, FALSE);

		//HPゲージの表示
		RECT rect = { -5.0f,20.0f,5.0f,18.0f };
		hpGauge->drawModiBillboard(enemyPos[i],rect,0);	//赤ゲージ

		int extSize = hp[i];	//緑ゲージのサイズを算出
		
		//画像幅:rect.right - rect.leftで求めた値
		float oneScale = (rect.right-rect.left)/static_cast<float>(maxHp);		//画像幅÷最大HP＝＞1メモリのサイズ
		float gaugeW = static_cast<float>(hp[i]) * oneScale;	//体力数分の幅
		if (gaugeW < 0)gaugeW = 0;

		RECT rect2{ -5.0f,20.0f ,gaugeW-5.0f ,18};  //初期化と変数設定を同時にしている
		hpGauge->drawModiBillboard(enemyPos[i], rect2, 1);	//緑ゲージ
	}
}

//体力を減らす
void Enemy::TakeDamage(int index,int damage) {
	hp[index] -= damage;
}

int Enemy::GetHp(int index) {	//体力を取得

	return hp[index];
}

//初期位置の設定
void Enemy::initPosition(int index) {	

	dir[index] = static_cast<DIRECTION>(GetRand(3));	//０～３の乱数

	float x{}, z{};
	switch (dir[index]) {

	case DIRECTION::DOWN:	//手前向き
		x = GetRand(100) - 50;//-50～50の乱数
		z = -200;
		break;
	case DIRECTION::LEFT:	//左向き
		x = 200;
		z = GetRand(100) - 50;//-50～50の乱数
		break;
	case DIRECTION::UP:	//奥向き
		x = GetRand(100) - 50;//-50～50の乱数
		z = -200;
		break;
	case DIRECTION::RIGHT:	//右向き
		x = -200;
		z = GetRand(100) - 50;//-50～50の乱数
		break;
	}


	enemyPos[index] = VGet(x, 0, z);
	isDead[index] = false;
	hp[index] = maxHp;
}
