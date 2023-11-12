#include "Main.h"


//==============================================================
// ＜CShtGame＞關卡的構築（子彈）
void CShtGame::MakeStages_Bullet() {
	CMover *stage, *enemy[100], *bullet[100], *crash[100];	
	CMoverGroup* sg=MoverGroupManager->GetGroup(STAGE_GROUP);
	CMoverGroup* bg=MoverGroupManager->GetGroup(BULLET_GROUP);
	CMoverGroup* eg=MoverGroupManager->GetGroup(ENEMY_GROUP);

	//==========================================================
	// 瞄準彈
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
	AddStage(stage, "瞄準彈", "向自機發射的子彈。");

	//==========================================================
	// 瞄準彈2
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
	AddStage(stage, "瞄準彈2", "速度不同的兩種的瞄準彈。");
	
	//==========================================================
	// 瞄準彈（DDA）
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
	AddStage(stage, "瞄準彈（DDA）", "使用DDA的瞄準彈。");
	
	//==========================================================
	// 瞄準彈（固定小數點）
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
	AddStage(stage, "瞄準彈（固定小數點）", "使用固定小數點的瞄準彈。");
	
	//==========================================================
	// 方向彈
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
	AddStage(stage, "方向彈", "朝指定方向飛行的子彈");

	//==========================================================
	// 使用Table的方向彈
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
	AddStage(stage, "使用Table的方向彈", "以速度3朝向16個方向射出的子彈。\n");

	//==========================================================
	// 方向彈（DDA）
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
	AddStage(stage, "方向彈（DDA）", "使用DDA的方向彈。");

	//==========================================================
	// n-way彈
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
	AddStage(stage, "n-way彈", "以扇形射出的子彈。");

	//==========================================================
	// 圓形彈
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
	AddStage(stage, "圓形彈", "全方位圓形散射出去的子彈。");

	//==========================================================
	// 分裂彈
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
	AddStage(stage, "分裂彈", "會分裂好幾個的子彈射出。");

	//==========================================================
	// 簡易誘導彈
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
	AddStage(stage, "簡易誘導彈", "使用了單純誘導演算法的子彈。");

	//==========================================================
	// 誘導彈
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
	AddStage(stage, "誘導彈", "會追蹤自機的誘導彈。");

	//==========================================================
	// 誘導雷射
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
	AddStage(stage, "誘導雷射", "會追蹤自機的雷射。");

#ifndef CMAGA6

	//==========================================================
	// 誘導雷射2
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
	AddStage(stage, "誘導雷射2", "會在途中中止誘導以直線前進的雷射。");

#endif

	//==========================================================
	// 導引飛彈
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
	AddStage(stage, "導引飛彈", "會追蹤自機的飛彈。");

	//==========================================================
	// 加速n-way彈
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
	AddStage(stage, "加速n-way彈", "射出後會漸加速的n-way彈。");

	//==========================================================
	// 加速誘導雷射
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
	AddStage(stage, "加速誘導雷射", "會重複加速和減速的誘導雷射。");

	//==========================================================
	// 墜落彈
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
	AddStage(stage, "墜落彈", "會依重力墜落的子彈。", VIEW_SIDE);

	//==========================================================
	// 墜落飛彈
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
	AddStage(stage, "墜落飛彈", "會依重力墜落的飛彈。", VIEW_SIDE);

	//==========================================================
	// 旋轉彈
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
	AddStage(stage, "旋轉彈", "圍繞著中心點周圍旋轉的子彈。");

	//==========================================================
	// 旋轉彈2
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
	AddStage(stage, "旋轉彈2", "依不同半徑旋轉的子彈。");

	//==========================================================
	// 瞄準彈+旋轉彈
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
	AddStage(stage, "瞄準彈+旋轉彈", "朝自機方向射來的子彈與旋轉彈所組合而成。");

	//==========================================================
	// 漩渦彈
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
	AddStage(stage, "漩渦彈", "會呈漩渦狀散開的子彈。");

	//==========================================================
	// 會停止的誘導彈
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
	AddStage(stage, "會停止的誘導彈", "會在途中停止然後又移動追向自機的子彈。");

	//==========================================================
	// 會逃離的誘導雷射
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
	AddStage(stage, "會逃離的誘導雷射", "會重複追蹤與逃離的誘導雷射。");

	//==========================================================
	// 直進光束
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
	AddStage(stage, "直進光束", "朝直線方向前進的粗大光束。");

	//==========================================================
	// 安全地帶
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_BLUE])
		->SetDirected(0.3f, 0.25f)
		->SetYaw(0.01f);
	stage=(new CMover(sg))
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->SetPos(37.5f, 0)
		->AddSpawnNWay(bullet[0], 0, 40, -1, 19, 0.02f);
	AddStage(stage, "安全地帶", "在安全地帶的單純n-way彈範例。");

	//==========================================================
	// 安全地帶2
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
	AddStage(stage, "安全地帶2", "加上瞄準彈的安全地帶的範例。");

	//==========================================================
	// 亂數
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_BLUE])
		->SetAiming(0.8f, 0)
		->SetYaw(0.01f);
	stage=(new CMover(sg))
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->SetPos(37.5f, 0)
		->AddSpawnNWay(bullet[0], 0, 10, -1, 5, 0.02f);
	AddStage(stage, "亂數", "使用亂數的單純n-way彈。");

	//==========================================================
	// 亂數2
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_PURPLE])
		->SetAiming(0.8f, 0)
		->SetRand(0.2f, 0.05f)
		->SetYaw(0.01f);
	stage=(new CMover(sg))
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->SetPos(37.5f, 0)
		->AddSpawnNWay(bullet[0], 0, 10, -1, 5, 0.02f);
	AddStage(stage, "亂數2", "方向與速度以亂數呈現的n-way彈。");
}

