#include "gameManager.h"
#include "camera.h"
#include "stage.h"
#include "player.h"
#include "shot.h"
#include "enemy.h"
#include "explosion.h"
#include "softcream.h"

// クラス宣言
class Camera*	camera;	// ｶﾒﾗｸﾗｽ
class Stage*	stage;	// ｽﾃｰｼﾞｸﾗｽ
class Player*	player;	// ﾌﾟﾚｲﾔｰｸﾗｽ
class Shot*		shot;	// 弾ｸﾗｽ
class Enemy*	enemy;	// 敵ｸﾗｽ
class Explosion* explosion;	//爆発ｸﾗｽ
class Softcream* softcream;	//ソフトクリームｸﾗｽ

// ｺﾝｽﾄﾗｸﾀ(初期処理)
GameManager::GameManager()
{
	camera	= new Camera;	// ｶﾒﾗｸﾗｽの生成
	stage	= new Stage;	// ｽﾃｰｼﾞｸﾗｽの生成
	player	= new Player;	// ﾌﾟﾚｲﾔｰｸﾗｽの生成
	shot	= new Shot;		// 弾ｸﾗｽの生成
	enemy	= new Enemy;	// 敵ｸﾗｽの生成
	explosion = new Explosion;	// 爆発ｸﾗｽの生成
	softcream = new Softcream;	// ソフトクリームｸﾗｽの生成

	explosionSE = new Sound;	// 爆発音
	explosionSE->loadSound(
		"sound/maou_se_battle_explosion06.mp3");

	addFont("font//Geostar-Regular.ttf");
	changeFont("Geostar");					//文字フォントの変更
	//changeFont("殴り書きクレヨン");
	setFontSize(40);				//ﾌｫﾝﾄｻｲｽﾞの変更
	setTextColor(155, 255, 255);	//文字色

	//カメラ位置の設定
	//camera->setCamera(VGet(0, 20.0f, -0.1f), VGet(0, 0, 0));
}

// ﾃﾞｽﾄﾗｸﾀ(終了処理)
GameManager::~GameManager()
{
	delete camera;	// ｶﾒﾗｸﾗｽを破棄
	delete stage;	// ｽﾃｰｼﾞｸﾗｽを破棄
	delete player;	// ﾌﾟﾚｲﾔｰｸﾗｽを破棄
	delete shot;	// 弾ｸﾗｽを破棄
	delete enemy;	// 敵ｸﾗｽを破棄
	delete explosion;	// 爆発ｸﾗｽを破棄
	delete softcream;	// ソフトクリームｸﾗｽを破棄

	delete explosionSE;	// 爆発音を破棄

	removeFont();	//ﾌﾘｰﾌｫﾝﾄの削除
}

//初期化処理
void GameManager::Init()
{
	stage->Init();
	player->Init();
	shot->Init();
	enemy->Init();
	explosion->Init();

	score = 0;
}
//更新処理
void GameManager::Update()
{
	camera->moveCamera();	//ｶﾒﾗの移動
	camera->moveLook();		//注視位置の移動

	oldScene = stage->getScene();	//変更前のｼｰﾝを取得

	stage->Update();
	//カメラ位置の設定

	

	if (stage->getScene() != oldScene) {
		//シーンが切り替わった時
			Init();
	}
	if (stage->getScene() == SCENE::GAME) {

		//カメラ位置の設定（ゲーム中：プレイヤーの位置を追尾）
		VECTOR cameraPos, lookPos;
		cameraPos = lookPos = player->getPosition();
		cameraPos.y = 100.0f;
		cameraPos.z -= 50.1f;
		lookPos.y = 0;
		lookPos.z += -10.0f;
		//camera->setCamera(VGet(0, 500.0f, -0.1f), VGet(0, 0, 0));
		camera->setCamera(cameraPos,lookPos);
	}
	else {
		//カメラ位置の設定（ゲーム中以外）
		camera->setCamera(VGet(0, 10.0f, -100.0f), VGet(0, 5.0f, 100.0f));
	}
		//ゲーム中以外はリターン
	if (stage->getScene() != SCENE::GAME)  return;
	

	


	player->Update();
	// 弾にﾌﾟﾚｲﾔｰの位置を設定
	shot->setPlayerPos(player->getPosition(),player->getDirection());
	shot->Update();
	

	//敵にプレイヤーの位置を設定
	enemy->setPlayerPos(player->getPosition());
	enemy->Update();

	// 弾と敵の当たり判定
	for (int i = 0; i < Shot::SHOTMAX; i++)
	{
		VECTOR center1 = shot->getPosition(i);	// 弾の位置
		float r1 = shot->getRadius();	// 弾の半径

		for (int ecnt = 0; ecnt < Enemy::ENEMYMAX; ecnt++)
		{
			VECTOR center2 = enemy->getPosition(ecnt);	// 敵の位置
			float r2 = enemy->getRadius();	// 敵の半径
			center2.y += 7.0f;	//敵の判定の高さを調整
			
			if (hitCheck_Sphere(center1, r1, center2, r2))
			{
				// === 命中した時 ===
				shot->Init(i);		//弾を初期化
				// 敵の位置を爆発に設定
				explosion->setPosition(center2);

				enemy->TakeDamage(ecnt, 1);//敵にダメージ
				if(enemy->GetHp(ecnt)<=0)	enemy->Init(ecnt);	// 敵を初期化
				score += 100;		//点数を加算

				explosionSE->playSound(FALSE);//爆発音
				break;
			}
		}
	}

	// プレイヤーと敵の当たり判定
	if (!player->GetIsDead()) {//死んでいない時
		VECTOR center1 = player->getPosition();	// ﾌﾟﾚｲﾔｰの位置
		float r1 = player->getRadius();			// ﾌﾟﾚｲﾔｰの半径
		center1.y += 2.5f;	//ﾌﾟﾚｲﾔｰの判定の高さを調整
		for (int ecnt = 0; ecnt < Enemy::ENEMYMAX; ecnt++)
		{
			VECTOR center2 = enemy->getPosition(ecnt);	// 敵の位置
			float r2 = enemy->getRadius();	// 敵の半径
			center2.y += 7.0f;	//敵の判定の高さを調整

			if (hitCheck_Sphere(center1, r1, center2, r2))
			{
				// === 命中した時 ===
				// ﾌﾟﾚｲﾔｰの位置を爆発に設定
				explosion->setPosition(center1);
				explosionSE->playSound(FALSE);	// 爆発音
				player->SetIsDead(100);			//無敵時間
				//player->TakeDamage(32);			//ダメージ
				player->TakeDamage();			//残機を減らす
				break;
			}
		}
	}

	//プレイヤー壁の当たり判定
	//VECTOR center = player->getPosition();	// ﾌﾟﾚｲﾔｰの位置
	float r = player->getRadius();			// ﾌﾟﾚｲﾔｰの半径
	//center.y += 2.5f;	//ﾌﾟﾚｲﾔｰの判定の高さを調整
	//if (hitCheck_Sphere(stage->getMHandle(),center, r)) 

	VECTOR p1, p2;
	p1 = p2= player->getPosition();
	p1.y+= 10.5f;
	p2.y += 3.0f;

	if (hitCheck_Capsule(stage->getMHandle(),p1,p2, r))
	{
		//壁に当たった時
		DrawFormatString(10, 150, GetColor(255, 255, 255), "WallHit!");
		player->MoveReset();	//移動前に戻す
	}
	
	//プレイヤーの線とオブジェクト（ソフトクリーム）の当たり判定
	VECTOR startPos, endPos, crossPos;
	isHit = false;
	player->GetLinePos(&startPos, &endPos);//開始・終了位置を取得
	if (hitCheck_Line(
		softcream->getMHandle(),
		startPos, endPos, &crossPos)) {

		isHit = true;	//当たっている
		sprintf_s(dbgMsg, "Hit softcream[x:%0.1f,y:%0.1f,z:%0.1f]", crossPos.x, crossPos.y, crossPos.z);
	}

	//プレイヤーの高さ判定
	VECTOR topPos, bottomPos, p;
	p=player->getPosition();	//プレイヤーのポジションをコピー
	topPos = VGet(p.x, p.y + 7.0f, p.z);
	bottomPos = VGet(p.x, p.y - 25.0f, p.z);
	if (hitCheck_Line(stage->getMHandle(), topPos, bottomPos, &crossPos)) {

		p.y = crossPos.y;//Y座標を地面の高さにする
		player->setPosition(p);	//プレイヤーの位置を更新
	}


	if (player->GetIsDead())	//死亡中の時
	{
		if (player->GetDeadCnt())	//ｼｰﾝ切り換えまでのｶｳﾝﾄ
		{
			if(player->GetLives()<=0)  
				stage->setScene(SCENE::OVER);	// ｹﾞｰﾑｵｰﾊﾞｰへ
		}
	}

	//ゲームクリア処理
	if (score > 10000) {
		player->setPosition(VGet(0, 0, -80));
		player->setRotation(VGet(0, 0, 0));
		stage->setScene(SCENE::CLEAR);	//ｹﾞｰﾑｸﾘｱへ
	}

}
// 表示処理
void GameManager::Draw()
{
	stage->Draw();	// ｽﾃｰｼﾞ

	switch (stage->getScene())
	{
	case SCENE::TITLE:	// ﾀｲﾄﾙ画面
		player->DrawTitle();// ﾌﾟﾚｲﾔｰ
		break;

	case SCENE::GAME:	// ｹﾞｰﾑ中

		softcream->Draw();	//ｿﾌﾄｸﾘｰﾑ

		player->Draw();		// ﾌﾟﾚｲﾔｰ
		enemy->Draw();		// 敵
		explosion->Draw();	//爆発の表示

		shot->Draw();	// 弾

		//点数
		char str[32];
		wsprintf(str, "SCORE:%06d", score);
		drawString(10, 10, str);

		//デバッグ表示
		if (isHit) {
			drawString(10, 100, dbgMsg);
		}
		break;


	case SCENE::OVER:	// ｹﾞｰﾑｵｰﾊﾞｰ
		player->DrawOver();	// ﾌﾟﾚｲﾔｰ
		break;

	case SCENE::CLEAR:	// ｹﾞｰﾑｸﾘｱ
		player->DrawClear();	//プレイヤー

		break;
	}
}

// 球の当たり判定(計算版)
bool GameManager::hitCheck_Sphere(
	VECTOR center1, float r1,	// Aの中心座標と半径
	VECTOR center2, float r2)	// Bの中心座標と半径
{
	// 中心点の距離を求める
	// a^2 + b^2 + c^2
	float centerLength =
		(center1.x - center2.x) * (center1.x - center2.x)//a^2
	  + (center1.y - center2.y) * (center1.y - center2.y)//b^2
	  + (center1.z - center2.z) * (center1.z - center2.z);//d^2

	// 半径の足し算を2乗したものと中心点の距離を比べる
	// (r1 + r2)^2 > centerLength
	if ((r1 + r2) * (r1 + r2) > centerLength)
	{
		return true;	//当たっている
	}
	return false;	//外れている
}

// 球の当たり判定
bool GameManager::hitCheck_Sphere(int MHandle, VECTOR pos, float r) {

	MV1_COLL_RESULT_POLY_DIM hitPoly;	//判定結果構造体
	hitPoly = MV1CollCheck_Sphere(
		MHandle,	//予めsetupCollInfoしたﾓﾃﾞﾙﾊﾝﾄﾞﾙ
		-1,			//判定するﾌﾚｰﾑ番号（全体なら-1）
		pos,		//衝突するオブジェクトの中心座標
		r);			//衝突するオブジェクトの半径

	if (hitPoly.HitNum >= 1) {
		//1ポリゴン以上当たっている時
		return true;	//当たり
	}
	return false;		//外れ
}

bool GameManager::hitCheck_Capsule(
	int MHandle, VECTOR pos1, VECTOR pos2, float r) {

	MV1_COLL_RESULT_POLY_DIM hitPoly;	//判定結果構造体
	hitPoly = MV1CollCheck_Capsule(
		MHandle,	//予めsetupCollInfoしたﾓﾃﾞﾙﾊﾝﾄﾞﾙ
		-1,			//判定するﾌﾚｰﾑ番号（全体なら-1）
		pos1,		//衝突するオブジェクトの上半球の中心座標
		pos2,		//衝突するオブジェクトの下半球の中心座標
		r);			//衝突するオブジェクトの半径

	if (hitPoly.HitNum >= 1) {
		//1ポリゴン以上当たっている時
		return true;	//当たり
	}
	return false;		//外れ
}

//線の当たり判定
bool GameManager::hitCheck_Line(int MHandle, VECTOR startPos, VECTOR endPos, VECTOR* crossPos) {

	MV1_COLL_RESULT_POLY hitPoly;	//判定結果構造体	線の時は_DIMはいらない
	hitPoly= MV1CollCheck_Line(
		MHandle,	//ﾓﾃﾞﾙﾊﾝﾄﾞﾙ
		-1,			//ﾓﾃﾞﾙ全体
		startPos,endPos);		//開始・終了位置
		
	if(hitPoly.HitFlag == 1) {
				//当たった時
		*crossPos = hitPoly.HitPosition;	//交点座標を返す
		return true;	//当たり
	}
	return false;		//外れ
}