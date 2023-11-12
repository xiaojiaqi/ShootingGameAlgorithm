#include "Main.h"


//==============================================================
// ＜CShtGame＞ステージの構築（弾）
void CShtGame::MakeStages_Bullet() {
	CMover *stage, *enemy[100], *bullet[100], *crash[100];	
	CMoverGroup* sg=MoverGroupManager->GetGroup(STAGE_GROUP);
	CMoverGroup* bg=MoverGroupManager->GetGroup(BULLET_GROUP);
	CMoverGroup* eg=MoverGroupManager->GetGroup(ENEMY_GROUP);

	//==========================================================
	// 狙い撃ち弾
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_BLUE])
		->SetAiming(0.6f, 0)
		->SetYaw(0.05f);
	enemy[0]=(new CMover(eg))
		->SetObj3D(Obj3D[ENEMY])
		->SetAiming(0.3f, 0)
		->SetAutoYaw()
		->AddSpawn(bullet[0], 0, 20, -1);
	stage=(new CMover(sg))
		->SetPos(37.5f, -2)
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->AddSpawn(enemy[0], 1, 60, -1);
	AddStage(stage, "狙い撃ち弾", "自機に向かって飛ぶ弾。");

	//==========================================================
	// 狙い撃ち弾２
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_BLUE])
		->SetAiming(0.5f, 0)
		->SetYaw(0.05f);
	bullet[1]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_PURPLE])
		->SetAiming(0.7f, 0)
		->SetYaw(0.05f);
	enemy[0]=(new CMover(eg))
		->SetObj3D(Obj3D[ENEMY])
		->SetAiming(0.3f, 0)
		->SetAutoYaw()
		->AddSpawn(bullet[0], 0, 40, -1)
		->AddSpawn(bullet[1], 20, 40, -1);
	stage=(new CMover(sg))
		->SetPos(37.5f, -2)
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->AddSpawn(enemy[0], 1, 80, -1);
	AddStage(stage, "狙い撃ち弾２", "速度が違う２種類の狙い撃ち弾。");
	
	//==========================================================
	// 狙い撃ち弾（DDA）
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_BLUE])
		->SetAimingDDA(0.6f, 0)
		->SetYaw(0.05f);
	enemy[0]=(new CMover(eg))
		->SetObj3D(Obj3D[ENEMY])
		->SetAimingDDA(0.3f, 0)
		->SetAutoYaw()
		->AddSpawn(bullet[0], 0, 20, -1);
	stage=(new CMover(sg))
		->SetPos(37.5f, -2)
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->AddSpawn(enemy[0], 1, 60, -1);
	AddStage(stage, "狙い撃ち弾（DDA）", "DDAを使った狙い撃ち弾。");
	
	//==========================================================
	// 狙い撃ち弾（固定小数点数）
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_BLUE])
		->SetAimingFPN(0.6f, 0)
		->SetYaw(0.05f);
	enemy[0]=(new CMover(eg))
		->SetObj3D(Obj3D[ENEMY])
		->SetAimingFPN(0.3f, 0)
		->SetAutoYaw()
		->AddSpawn(bullet[0], 0, 20, -1);
	stage=(new CMover(sg))
		->SetPos(37.5f, -2)
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->AddSpawn(enemy[0], 1, 60, -1);
	AddStage(stage, "狙い撃ち弾（固定小数点数）", "固定小数点数を使った狙い撃ち弾。");
	
	//==========================================================
	// 方向弾
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_BLUE])
		->SetDirected(0.3f, 0.4f)
		->SetYaw(0.05f);
	bullet[1]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_PURPLE])
		->SetDirected(0.3f, 0.9f)
		->SetYaw(0.05f);
	enemy[0]=(new CMover(eg))
		->SetObj3D(Obj3D[ENEMY])
		->SetDirected(0.3f, 0.15f)
		->SetAutoYaw()
		->AddSpawn(bullet[0], 0, 15, -1)
		->AddSpawn(bullet[1], 0, 15, -1);
	stage=(new CMover(sg))
		->SetPos(-2, -2)
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->AddSpawn(enemy[0], 0, 80, -1);
	AddStage(stage, "方向弾", "指定した方向に飛ぶ弾。");

	//==========================================================
	// テーブルを使った方向弾
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_BLUE])
		->SetDirected16_3(0.4f, 0.4f)
		->SetYaw(0.05f);
	bullet[1]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_PURPLE])
		->SetDirected16_3(0.4f, 0.9f)
		->SetYaw(0.05f);
	enemy[0]=(new CMover(eg))
		->SetObj3D(Obj3D[ENEMY])
		->SetDirected16_3(0.4f, 0.15f)
		->SetAutoYaw()
		->AddSpawn(bullet[0], 0, 15, -1)
		->AddSpawn(bullet[1], 0, 15, -1);
	stage=(new CMover(sg))
		->SetPos(-2, -2)
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->AddSpawn(enemy[0], 0, 80, -1);
	AddStage(stage, "テーブルを使った方向弾", "１６方向、速度３のテーブルを使った方向弾。\n");

	//==========================================================
	// 方向弾（DDA）
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_BLUE])
		->SetDirectedDDA(0.3f, 0.4f)
		->SetYaw(0.05f);
	bullet[1]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_PURPLE])
		->SetDirectedDDA(0.3f, 0.9f)
		->SetYaw(0.05f);
	enemy[0]=(new CMover(eg))
		->SetObj3D(Obj3D[ENEMY])
		->SetDirectedDDA(0.3f, 0.15f)
		->SetAutoYaw()
		->AddSpawn(bullet[0], 0, 15, -1)
		->AddSpawn(bullet[1], 0, 15, -1);
	stage=(new CMover(sg))
		->SetPos(-2, -2)
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->AddSpawn(enemy[0], 0, 80, -1);
	AddStage(stage, "方向弾（DDA）", "DDAを使った方向弾。");

	//==========================================================
	// n-way弾
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[NEEDLE_SMALL_BLUE])
		->SetDirected(0.3f, 0.25f)
		->SetAutoYaw();
	bullet[1]=(new CMover(bg))
		->SetObj3D(Obj3D[NEEDLE_SMALL_PURPLE])
		->SetDirected(0.3f, 0.25f)
		->SetAutoYaw();
	stage=(new CMover(sg))
		->SetPos(37.5f, 0)
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->AddSpawnNWay(bullet[0], 0, 40, -1, 32, 0.01f)
		->AddSpawnNWay(bullet[1], 20, 40, -1, 33, 0.01f);
	AddStage(stage, "n-way弾", "扇状に広がる弾。");

	//==========================================================
	// 円形弾
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[NEEDLE_SMALL_BLUE])
		->SetAiming(0.3f, 0)
		->SetAutoYaw();
	bullet[1]=(new CMover(bg))
		->SetObj3D(Obj3D[NEEDLE_SMALL_PURPLE])
		->SetAiming(0.3f, 0)
		->SetAutoYaw();
	stage=(new CMover(sg))
		->SetPos(37.5f, 50)
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->AddSpawnCircle(bullet[0], 0, 40, -1, 80, false)
		->AddSpawnCircle(bullet[1], 20, 40, -1, 80, true);
	AddStage(stage, "円形弾", "円形に広がる弾。");

	//==========================================================
	// 分裂弾
	bullet[2]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_BLUE])
		->SetAiming(0.5f, 0)
		->SetYaw(0.01f);
	bullet[3]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_PURPLE])
		->SetAiming(0.6f, 0)
		->SetYaw(0.05f);
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_MEDIUM_BLUE])
		->SetAiming(0.3f, 0)
		->SetYaw(0.01f)
		->AddSpawnNWay(bullet[2], 60, 0, 1, 7, 0.02f)
		->SetNext(NULL, 62);
	bullet[1]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_MEDIUM_PURPLE])
		->SetAiming(0.4f, 0)
		->SetYaw(0.05f)
		->AddSpawnNWay(bullet[3], 60, 0, 1, 8, 0.02f)
		->SetNext(NULL, 62);
	stage=(new CMover(sg))
		->SetPos(37.5f, 0)
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->AddSpawn(bullet[0], 0, 40, -1)
		->AddSpawn(bullet[1], 20, 40, -1);
	AddStage(stage, "分裂弾", "分裂する弾。");

	//==========================================================
	// 簡易誘導弾
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_BLUE])
		->SetSimpleHoming(0.6f)
		->SetYaw(0.01f);
	bullet[1]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_PURPLE])
		->SetSimpleHoming(1.2f)
		->SetYaw(0.01f);
	stage=(new CMover(sg))
		->SetPos(37.5f, 0)
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->AddSpawn(bullet[0], 1, 30, -1)
		->AddSpawn(bullet[1], 15, 30, -1);
	AddStage(stage, "簡易誘導弾", "単純な誘導アルゴリズムを使った弾。");

	//==========================================================
	// 誘導弾
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_BLUE])
		->SetHoming(0.6f, 0.003f)
		->SetYaw(0.01f);
	bullet[1]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_PURPLE])
		->SetHoming(1.2f, 0.003f)
		->SetYaw(0.01f);
	stage=(new CMover(sg))
		->SetPos(37.5f, 0)
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->AddSpawn(bullet[0], 1, 30, -1)
		->AddSpawn(bullet[1], 15, 30, -1);
	AddStage(stage, "誘導弾", "誘導をあまくした誘導弾。");

	//==========================================================
	// 誘導レーザー
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[LASER_THIN_BLUE])
		->SetHoming(0.6f, 0.003f)
		->SetAutoYaw()
		->SetLaser(40, -0.02f, true);
	bullet[1]=(new CMover(bg))
		->SetObj3D(Obj3D[LASER_THIN_PURPLE])
		->SetHoming(1.2f, 0.003f)
		->SetAutoYaw()
		->SetLaser(80, -0.01f, true);
	stage=(new CMover(sg))
		->SetPos(37.5f, 0)
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->AddSpawn(bullet[0], 1, 60, -1)
		->AddSpawn(bullet[1], 30, 60, -1);
	AddStage(stage, "誘導レーザー", "自機を追いかけるレーザー。");

#ifndef CMAGA6

	//==========================================================
	// 誘導レーザー２
	bullet[1]=(new CMover(bg))
		->SetObj3D(Obj3D[LASER_THIN_BLUE])
		->SetDirected(0.6f, -0.25f)
		->SetAutoYaw()
		->SetLaser(40, -0.02f, true);
	bullet[0]=(new CMover(bullet[1]))
		->SetDirected(0.6f, -0.2f)
		->SetHoming(0.01f)
		->AddSpawn(bullet[1], 60, 0, 1)
		->SetNext(NULL, 60);
	bullet[3]=(new CMover(bg))
		->SetObj3D(Obj3D[LASER_THIN_PURPLE])
		->SetDirected(0.6f, -0.25f)
		->SetAutoYaw()
		->SetLaser(40, -0.02f, true);
	bullet[2]=(new CMover(bullet[3]))
		->SetDirected(0.6f, 0.7f)
		->SetHoming(0.01f)
		->AddSpawn(bullet[3], 60, 0, 1)
		->SetNext(NULL, 60);
	enemy[0]=(new CMover(eg))
		->SetPos(0, 20)
		->AddSpawn(bullet[0], 0, 100, -1);
	enemy[1]=(new CMover(eg))
		->SetPos(75, 20)
		->AddSpawn(bullet[2], 50, 100, -1);
	enemy[2]=(new CMover(eg))
		->SetPos(0, 60)
		->AddSpawn(bullet[0], 0, 100, -1);
	enemy[3]=(new CMover(eg))
		->SetPos(75, 60)
		->AddSpawn(bullet[2], 50, 100, -1);
	stage=(new CMover(sg))
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->AddSpawn(enemy[0], 1, 0, 1)
		->AddSpawn(enemy[1], 1, 0, 1)
		->AddSpawn(enemy[2], 1, 0, 1)
		->AddSpawn(enemy[3], 1, 0, 1);
	AddStage(stage, "誘導レーザー２", "途中で誘導をやめて直進するレーザー。");

#endif

	//==========================================================
	// 誘導ミサイル
	crash[0]=(new CMover(bg))
		->SetObj3D(Obj3D[CRASH_MISSILE])
		->SetScale(0.5f, 0.5f, 0.1f, 0.1f)
		->SetAlpha(2, -0.04f)
		->SetNext(NULL, 50);
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[MISSILE_SMALL])
		->SetHoming(0.8f, 0.001f)
		->SetAutoYaw()
		->SetAutoRoll(0.1f, 0.01f)
		->AddSpawn(crash[0], 100, 0, 1)
		->SetNext(NULL, 100)
		->SetLaser(40, -0.025f, false, Obj3D[MISSILE_TAIL_SMALL], true, true)
		->SetDamage(1, 1, crash[0], NULL, false, false);
	stage=(new CMover(sg))
		->SetPos(37.5f, 0)
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->AddSpawn(bullet[0], 1, 30, -1);
	AddStage(stage, "誘導ミサイル", "自機を追いかけるミサイル。");

	//==========================================================
	// 加速n-way弾
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_BLUE])
		->SetDirected(0.01f, 0.25f)
		->SetYaw(0.05f)
		->SetAccel(0.005f);
	bullet[1]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_PURPLE])
		->SetDirected(0.01f, 0.25f)
		->SetYaw(0.05f)
		->SetAccel(0.005f);
	stage=(new CMover(sg))
		->SetPos(37.5f, 0)
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->AddSpawnNWay(bullet[0], 0, 40, -1, 32, 0.01f)
		->AddSpawnNWay(bullet[1], 20, 40, -1, 33, 0.01f);
	AddStage(stage, "加速n-way弾", "だんだん速度が上がるn-way弾。");

	//==========================================================
	// 加速誘導レーザー
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[LASER_THIN_BLUE])
		->SetHoming(0.2f, 0.003f)
		->SetAutoYaw()
		->SetAccel(0.01f)
		->SetLaser(40, -0.02f, true);
	bullet[1]=(new CMover(bg))->SetAccel(-0.01f);
	bullet[0]->SetNext(bullet[1], 60);
	bullet[1]->SetNext(bullet[0], 60);
	bullet[2]=(new CMover(bg))
		->SetObj3D(Obj3D[LASER_THIN_PURPLE])
		->SetHoming(0.4f, 0.003f)
		->SetAutoYaw()
		->SetAccel(0.02f)
		->SetLaser(40, -0.02f, true);
	bullet[3]=(new CMover(bg))->SetAccel(-0.02f);
	bullet[2]->SetNext(bullet[3], 40);
	bullet[3]->SetNext(bullet[2], 40);
	stage=(new CMover(sg))
		->SetPos(37.5f, 0)
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->AddSpawn(bullet[0], 1, 60, -1)
		->AddSpawn(bullet[2], 30, 60, -1);
	AddStage(stage, "加速誘導レーザー", "加速と減速を繰り返す誘導レーザー。");

	//==========================================================
	// 落下弾
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_BLUE])
		->SetDirected(1.2f, 0.7f)
		->SetYaw(-0.01f)
		->SetAccelXY(0, 0.01f);
	bullet[1]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_PURPLE])
		->SetDirected(0.6f, 0.5f)
		->SetYaw(-0.01f)
		->SetAccelXY(0, 0.01f);
	enemy[0]=(new CMover(eg))
		->SetPos(100, 75)
		->AddSpawn(bullet[0], 0, 10, -1);
	enemy[1]=(new CMover(eg))
		->SetPos(100, 25)
		->AddSpawn(bullet[1], 5, 10, -1);
	stage=(new CMover(sg))
		->AddSpawn(MyShipSideView, 0, 0, 1)
		->AddSpawn(enemy[0], 0, 0, 1)
		->AddSpawn(enemy[1], 0, 0, 1);
	AddStage(stage, "落下弾", "重力に引かれて落下する弾。", VIEW_SIDE);

	//==========================================================
	// 落下ミサイル
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[MISSILE_SMALL])
		->SetAiming(1.2f, 0)
		->SetAutoYaw()
		->SetAutoRoll(0.1f, 0.01f, true, false)
		->SetAccelXY(0, 0.01f)
		->AddSpawn(crash[0], 80, 0, 1)
		->SetNext(NULL, 80)
		->SetLaser(40, -0.025f, false, Obj3D[MISSILE_TAIL_SMALL], true, true)
		->SetDamage(1, 1, crash[0], NULL, false, false);
	enemy[0]=(new CMover(eg))
		->SetObj3D(Obj3D[ENEMY_CANNON])
		->SetDirected(0.4f, 0.5f)
		->SetYaw(0.01f)
		->AddSpawn(bullet[0], 0, 10, -1);
	enemy[1]=(new CMover(eg))->SetAccel(-0.1f);
	enemy[2]=(new CMover(eg))->SetAccel(0);
	enemy[3]=(new CMover(eg))->SetAccel(0.1f);
	enemy[0]->SetNext(enemy[1], 180);
	enemy[1]->SetNext(enemy[2], 7);
	enemy[2]->SetNext(enemy[3], 180);
	enemy[3]->SetNext(enemy[0], 7);
	stage=(new CMover(sg))
		->AddSpawn(MyShipSideView, 0, 0, 1)
		->SetPos(90, 70)
		->AddSpawn(enemy[0], 0, 0, 1);
	AddStage(stage, "落下ミサイル", "重力に引かれて落下するミサイル。", VIEW_SIDE);

	//==========================================================
	// 回転弾
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[NEEDLE_SMALL_BLUE])
		->SetLooping(0, 0.005f, 0, 15, 0, 0)
		->SetAutoYaw();
	bullet[1]=(new CMover(bg))
		->SetObj3D(Obj3D[NEEDLE_SMALL_PURPLE])
		->SetLooping(0, -0.0025f, 0, 30, 0, 0)
		->SetAutoYaw();
	stage=(new CMover(sg))
		->SetPos(37.5f, 50)
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->AddSpawnCircle(bullet[0], 0, 0, 1, 10, false)
		->AddSpawnCircle(bullet[1], 0, 0, 1, 20, false);
	AddStage(stage, "回転弾", "決まった点の周囲を回転する弾。");

	//==========================================================
	// 回転弾２
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_BLUE])
		->SetLooping(0, 0.001f, 0, 0, 0.2f, 0)
		->SetYaw(0.01f);
	bullet[1]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_PURPLE])
		->SetLooping(0, -0.001f, 0, 0, 0.3f, 0)
		->SetYaw(-0.01f);
	stage=(new CMover(sg))
		->SetPos(37.5f, 50)
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->AddSpawnCircle(bullet[0], 0, 40, -1, 10, false)
		->AddSpawnCircle(bullet[1], 20, 40, -1, 20, false);
	AddStage(stage, "回転弾２", "半径方向にだんだん広がる回転弾。");

	//==========================================================
	// 狙い撃ち弾＋回転弾
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_BLUE])
		->SetLooping(0, 0.001f, 0, 0, 0.1f, 0)
		->SetYaw(0.01f);
	bullet[1]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_PURPLE])
		->SetLooping(0, -0.001f, 0, 0, 0.2f, 0)
		->SetYaw(-0.01f);
	bullet[2]=(new CMover(bg))
		->SetAiming(0.6f, 0)
		->AddSpawnCircle(bullet[0], 0, 0, 1, 8, false)
		->AddSpawnCircle(bullet[1], 0, 0, 1, 16, false);
	stage=(new CMover(sg))
		->SetPos(37.5f, 0)
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->AddSpawn(bullet[2], 0, 60, -1);
	AddStage(stage, "狙い撃ち弾＋回転弾", "中心の動きを狙い撃ち弾と同じ動きにした回転弾。");

	//==========================================================
	// 渦巻き弾
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[NEEDLE_SMALL_BLUE])
		->SetDirected(0.2f, 0)
		->SetAutoYaw();
	bullet[1]=(new CMover(bg))
		->SetObj3D(Obj3D[NEEDLE_SMALL_PURPLE])
		->SetDirected(0.4f, 0)
		->SetAutoYaw();
	stage=(new CMover(sg))
		->SetPos(37.5f, 50)
		->SetYaw(0.01f)
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->AddSpawn(bullet[0], 0, 1, -1)
		->AddSpawn(bullet[1], 1, 1, -1);
	AddStage(stage, "渦巻き弾", "渦巻き状に広がる弾。");

	//==========================================================
	// 停止する誘導弾
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_BLUE])
		->SetHoming(0.6f, 0.003f)
		->SetYaw(0.01f);
	bullet[1]=(new CMover(bg))->SetAccel(-0.05f);
	bullet[2]=(new CMover(bg))->SetYaw(0);
	bullet[3]=(new CMover(bg))->SetAccel(0.05f);
	bullet[0]->SetNext(bullet[1], 60);
	bullet[1]->SetNext(bullet[2], 11);
	bullet[2]->SetNext(bullet[3], 30);
	bullet[3]->SetNext(bullet[0], 11);
	stage=(new CMover(sg))
		->SetPos(37.5f, 0)
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->AddSpawn(bullet[0], 0, 60, -1);
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_PURPLE])
		->SetHoming(0.6f, 0.003f)
		->SetYaw(0.01f);
	bullet[1]=(new CMover(bg))->SetAccel(-0.05f);
	bullet[2]=(new CMover(bg))->SetYaw(0);
	bullet[3]=(new CMover(bg))->SetAccel(0.05f);
	bullet[0]->SetNext(bullet[1], 40);
	bullet[1]->SetNext(bullet[2], 11);
	bullet[2]->SetNext(bullet[3], 10);
	bullet[3]->SetNext(bullet[0], 11);
	stage->AddSpawn(bullet[0], 30, 60, -1);
	AddStage(stage, "停止する誘導弾", "停止と移動を繰り返す誘導弾。");

	//==========================================================
	// 逃げる誘導レーザー
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[LASER_THIN_BLUE])
		->SetHoming(0.6f, 0.003f)
		->SetAutoYaw()
		->SetLaser(40, -0.02f, true);
	bullet[1]=(new CMover(bg))
		->SetHoming(0.03f)
		->SetAccel(-0.05f);
	bullet[2]=(new CMover(bg))
		->SetHoming(0.03f)
		->SetAccel(0.05f);
	bullet[0]->SetNext(bullet[1], 90);
	bullet[1]->SetNext(bullet[2], 30);
	bullet[2]->SetNext(bullet[0], 30);
	stage=(new CMover(sg))
		->SetPos(37.5f, 0)
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->AddSpawn(bullet[0], 0, 60, -1);
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[LASER_THIN_PURPLE])
		->SetHoming(0.8f, 0.003f)
		->SetAutoYaw()
		->SetLaser(40, -0.02f, true);
	bullet[1]=(new CMover(bg))
		->SetHoming(0.03f)
		->SetAccel(-0.08f);
	bullet[2]=(new CMover(bg))
		->SetHoming(0.03f)
		->SetAccel(0.08f);
	bullet[0]->SetNext(bullet[1], 40);
	bullet[1]->SetNext(bullet[2], 20);
	bullet[2]->SetNext(bullet[0], 20);
	stage->AddSpawn(bullet[0], 30, 60, -1);
	AddStage(stage, "逃げる誘導レーザー", "追跡と逃亡を繰り返す誘導レーザー。");

	//==========================================================
	// 直進するビーム
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[LASER_THICK_BLUE])
		->SetDirected(2.0f, 0.25f);
	enemy[0]=(new CMover(eg))
		->SetPos(37.5f, 0)
		->AddSpawn(bullet[0], 0, 1, -1)
		->SetNext(NULL, 25);
	enemy[1]=(new CMover(enemy[0]))
		->SetPos(15, 0);
	enemy[2]=(new CMover(enemy[0]))
		->SetPos(60, 0);
	stage=(new CMover(sg))
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->AddSpawn(enemy[0], 0, 70, -1)
		->AddSpawn(enemy[1], 40, 80, -1)
		->AddSpawn(enemy[2], 40, 90, -1);
	AddStage(stage, "直進するビーム", "決まった方向にまっすぐ進むビーム。");

	//==========================================================
	// 安全地帯
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_BLUE])
		->SetDirected(0.3f, 0.25f)
		->SetYaw(0.01f);
	stage=(new CMover(sg))
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->SetPos(37.5f, 0)
		->AddSpawnNWay(bullet[0], 0, 40, -1, 19, 0.02f);
	AddStage(stage, "安全地帯", "安全地帯がある単純なn-way弾の例。");

	//==========================================================
	// 安全地帯２
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_BLUE])
		->SetDirected(0.3f, 0.25f)
		->SetYaw(0.01f);
	bullet[1]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_PURPLE])
		->SetAiming(0.8f, 0)
		->SetYaw(0.01f);
	stage=(new CMover(sg))
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->SetPos(37.5f, 0)
		->AddSpawnNWay(bullet[0], 0, 40, -1, 19, 0.02f)
		->AddSpawn(bullet[1], 15, 30, -1);
	AddStage(stage, "安全地帯２", "狙い撃ち弾を加えて安全地帯をなくした例。");

	//==========================================================
	// 乱数
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_BLUE])
		->SetAiming(0.8f, 0)
		->SetYaw(0.01f);
	stage=(new CMover(sg))
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->SetPos(37.5f, 0)
		->AddSpawnNWay(bullet[0], 0, 10, -1, 5, 0.02f);
	AddStage(stage, "乱数", "乱数を使わない単純なn-way弾。");

	//==========================================================
	// 乱数２
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_PURPLE])
		->SetAiming(0.8f, 0)
		->SetRand(0.2f, 0.05f)
		->SetYaw(0.01f);
	stage=(new CMover(sg))
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->SetPos(37.5f, 0)
		->AddSpawnNWay(bullet[0], 0, 10, -1, 5, 0.02f);
	AddStage(stage, "乱数２", "方向と速度に乱数を加えたn-way弾。");
}

