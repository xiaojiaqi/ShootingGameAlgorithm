#include "Main.h"


//==============================================================
// ＜CShtGame＞關卡的構築（武器）
void CShtGame::MakeStages_Weapon() {
	CMover *stage, *enemy[100];
	CMoverGroup* mg=MoverGroupManager->GetGroup(MYSHIP_GROUP);
	CMoverGroup* sg=MoverGroupManager->GetGroup(STAGE_GROUP);
	CMoverGroup* bg=MoverGroupManager->GetGroup(BULLET_GROUP);
	CMoverGroup* eg=MoverGroupManager->GetGroup(ENEMY_GROUP);
	CMoverGroup* wg=MoverGroupManager->GetGroup(WEAPON_GROUP);
	CMoverGroup* gg=MoverGroupManager->GetGroup(GROUND_GROUP);
	CMover *myship;

	CMover* shot=(new CMover(wg))
		->SetObj3D(Obj3D[SHOT_SMALL])
		->SetDirected(3.0f, 0.75f)
		->SetDamage(1, 1, NULL, NULL, false, false);
	CMover* big_shot=(new CMover(wg))
		->SetObj3D(Obj3D[SHOT_MEDIUM])
		->SetDirected(3.0f, 0.75f)
		->SetDamage(1, 1, NULL, NULL, false, false);
	CMover* max_shot=(new CMover(wg))
		->SetObj3D(Obj3D[SHOT_LARGE])
		->SetDirected(3.0f, 0.75f)
		->SetDamage(1, 1, NULL, NULL, false, false);
	CMover* laser=(new CMover(wg))
		->SetObj3D(Obj3D[LASER_THICK_BLUE])
		->SetDirected(3.0f, 0.75f)
		->SetDamage(1, 1, NULL, NULL, false, false);
	CMover* lock_shot=(new CMover(wg))
		->SetObj3D(Obj3D[SHOT_MEDIUM])
		->SetAiming(3.0f, 0)
		->SetTarget(
			TG_LOCKED_ENEMY, 0, 
			(new CMover(wg))
				->SetObj3D(Obj3D[SHOT_MEDIUM])
				->SetDirected(3.0f, 0.75f)
				->SetDamage(1, 1, NULL, NULL, false, false)
				->SetLock(0))
		->SetAutoYaw()
		->SetDamage(1, 1, NULL, NULL, false, false);

	CMover* enemy_crash=(new CMover(sg))
		->AddSpawn((new CMover(sg))
			->SetObj3D(Obj3D[CRASH_ENEMY])
			->SetScale(0.5f, 0.5f, 0.1f, 0.1f)
			->SetAlpha(2, -0.04f)
			->SetNext(NULL, 50)
			, 0, 0, 1);

#ifndef CMAGA6

	//==========================================================
	// 基本的射擊操作
	myship=(new CMover(MyShipTopView))
		->SetWeapon_Shot(WP_BASIC_SHOT, shot);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1);
	AddStage(stage, "基本的射擊操作", 
		"每次按押射擊鍵就會發射一次子彈。\n\n"
		"●發射●\n[X]鍵／按鈕2");

	//==========================================================
	// 連續射擊
	myship=(new CMover(MyShipTopView))
		->SetWeapon_Shot(WP_AUTO_SHOT, shot);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1);
	AddStage(stage, "連續射擊",
		"一直按押射擊鍵就會連續發射子彈。\n\n"
		"●發射●\n[X]鍵／按鈕2");

	//==========================================================
	// 集氣射擊
	myship=(new CMover(MyShipTopView))
		->SetWeapon_PowerShot(
			WP_POWER_SHOT, shot, big_shot, max_shot, 
			Obj3D[POWER_EFFECT], Obj3D[MAX_EFFECT],
			30, 120, 0);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1);
	AddStage(stage, "集氣射擊",
		"按住按鈕不放儲存能量，\n"
		"等集存能量後發射出大於一般射擊的子彈。\n\n"
		"●發射●\n[X]鍵／按鈕2");

	//==========================================================
	// 半自動連續射擊
	myship=(new CMover(MyShipTopView))
		->SetWeapon_PowerShot(
			WP_SEMI_AUTO_SHOT, shot, big_shot, max_shot, 
			Obj3D[POWER_EFFECT], Obj3D[MAX_EFFECT],
			15, 120, 15);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1);
	AddStage(stage, "半自動連續射擊", 
		"以某種程度的速度來連續按押按鈕，\n"
		"就會連續射擊\n\n"
		"●發射／集氣●\n[X]鍵／按鈕2");

	//==========================================================
	// 放開按鈕累積能量的集氣射擊
	myship=(new CMover(MyShipTopView))
		->SetWeapon_PowerShot(
			WP_POWER_SHOT_RELEASED, shot, big_shot, max_shot, 
			Obj3D[POWER_EFFECT], Obj3D[MAX_EFFECT],
			30, 120, 0);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1);
	AddStage(stage, "放開按鈕累積能量的集氣射擊",
		"利用放開按鍵來集氣，\n"
		"按下按鍵就發射。\n\n"
		"●發射●\n[X]鍵／按鈕2");

	//==========================================================
	// 連續射擊與雷射共存
	myship=(new CMover(MyShipTopView))
		->SetWeapon_Laser(WP_SHOT_AND_LASER, shot, laser, 15, 15);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1);
	AddStage(stage, "連續射擊與雷射共存",
		"有節奏地敲打按鍵則是一般射擊，\n"
		"按住按鍵不放則是雷射。\n\n"
		"●一般射擊／雷射●\n[X]鍵／按鈕2");

	//==========================================================
	// 鎖定射擊
	myship=(new CMover(MyShipTopView))
		->SetWeapon_Laser(WP_LOCK_SHOT, shot, lock_shot, 15, 15);
	enemy[0]=(new CMover(eg))
		->SetObj3D(Obj3D[ENEMY])
		->SetAiming(0.3f, 0)
		->SetAutoYaw()
		->SetDamage(1, 100, enemy_crash, NULL, false, false);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->SetPos(37.5f, 0)
		->AddSpawn(enemy[0], 0, 60, -1);
	AddStage(stage, "鎖定射擊",
		"有節奏地敲打按鍵是發射一般連續子彈，\n"
		"按著按鈕不放則朝固定的敵人持續鎖定射擊。\n\n"
		"●一般射擊／鎖定射擊●\n[X]鍵／按鈕2");

	//==========================================================
	// 指令射擊
	COMMAND_LIST* cmd_list=new COMMAND_LIST();
	cmd_list->NumCommand=2;
	COMMAND& cmd0=cmd_list->Command[0];
	cmd0.Length=3;
	cmd0.Limit=30;
	cmd0.Input[0]=CMD_DOWN;
	cmd0.Input[1]=CMD_DOWN|CMD_RIGHT;
	cmd0.Input[2]=CMD_RIGHT|CMD_BUTTON1;
	cmd0.Model=(new CMover(wg))
		->SetObj3D(Obj3D[SHOT_MEDIUM])
		->SetDirected(3.0f, 0.0f)
		->SetAutoYaw()
		->SetDamage(1, 1, NULL, NULL, false, false)
		->AddSpawn((new CMover(wg))
			->SetObj3D(Obj3D[SHOT_MEDIUM])
			->SetDirected(3.0f, -0.1f)
			->SetAutoYaw()
			->SetDamage(1, 1, NULL, NULL, false, false)
			, 0, 0, 1)
		->AddSpawn((new CMover(wg))
			->SetObj3D(Obj3D[SHOT_MEDIUM])
			->SetDirected(3.0f, 0.1f)
			->SetAutoYaw()
			->SetDamage(1, 1, NULL, NULL, false, false)
			, 0, 0, 1);
	COMMAND& cmd1=cmd_list->Command[1];
	cmd1.Length=3;
	cmd1.Limit=30;
	cmd1.Input[0]=CMD_RIGHT;
	cmd1.Input[1]=CMD_DOWN;
	cmd1.Input[2]=CMD_DOWN|CMD_RIGHT|CMD_BUTTON1;
	cmd1.Model=(new CMover(wg))
		->SetObj3D(Obj3D[SHOT_MEDIUM])
		->SetDirected(3.0f, 0.75f)
		->SetAutoYaw()
		->SetDamage(1, 1, NULL, NULL, false, false)
		->AddSpawn((new CMover(wg))
			->SetObj3D(Obj3D[SHOT_MEDIUM])
			->SetDirected(3.0f, 0.65f)
			->SetAutoYaw()
			->SetDamage(1, 1, NULL, NULL, false, false)
			, 0, 0, 1)
		->AddSpawn((new CMover(wg))
			->SetObj3D(Obj3D[SHOT_MEDIUM])
			->SetDirected(3.0f, 0.85f)
			->SetAutoYaw()
			->SetDamage(1, 1, NULL, NULL, false, false)
			, 0, 0, 1);
	myship=(new CMover(MyShipSideView))
		->SetWeapon_Command(WP_COMMAND_SHOT, cmd_list);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1);
	AddStage(stage, "指令射擊", 
		"組合按鍵輸入特別指令可發射特殊攻擊。\n\n"
		"●指令射擊1●\n下、右下、右、[X]鍵／按鈕2\n\n"
		"●指令射擊2●\n右、下、右下、[X]鍵／按鈕2"
		,VIEW_SIDE);

	//==========================================================
	// 使用瞄準器轟炸
	myship=(new CMover(MyShipTopView))
		->SetSightedBomb(
			0, -30, 
			Obj3D[SIGHT_BOMB_READY], 
			Obj3D[SIGHT_BOMB_LOCK], 
			Obj3D[SIGHT_BOMB_TARGET], 
			Obj3D[SIGHT_BOMB_BUSY],
			(new CMover(wg))
				->SetObj3D(Obj3D[SIGHT_BOMB_BOMB])
				->SetDirected(1.0f, 0.75f)
				->SetDamage(1, 1, NULL, NULL, false, true)
				->AddSpawn(
					(new CMover(wg))
						->SetObj3D(Obj3D[SIGHT_BOMB_BOMB])			
						->SetNext(NULL, 0)
						->SetDamage(1, 1, NULL, NULL, false, false),
					30, 0, 1)
				->SetNext(NULL, 30)
			);
	enemy[0]=(new CMover(eg))
		->SetObj3D(Obj3D[ENEMY])
		->SetAiming(0.3f, 0)
		->SetAutoYaw()
		->SetDamage(1, 1, enemy_crash, NULL, false, false);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->SetPos(37.5f, 0)
		->AddSpawn(enemy[0], 0, 60, -1);
	AddStage(stage, "使用瞄準器轟炸",
		"使用瞄準器來瞄準目標，然後投擲炸彈攻擊。\n\n"
		"●轟炸●\n[X]鍵／按鈕2");

	//==========================================================
	// 鎖定雷射
	CMover* lock_on_laser=(new CMover(wg))
		->SetObj3D(Obj3D[LASER_THIN_BLUE])
		->SetDirected(1.2f, 0.75f)
		->SetHoming(0.02f)
		->SetAccel(-0.001f)
		->SetAutoYaw()
		->SetDamage(1, 1, NULL, NULL, false, false, true)
		->SetLaser(40, -0.02f, true);
	myship=(new CMover(MyShipTopView))
		->SetLockonLaser(
			4, 0, -30, 
			Obj3D[SIGHT_BOMB_READY], 
			Obj3D[SIGHT_BOMB_LOCK], 
			Obj3D[SIGHT_BOMB_TARGET], 
			Obj3D[SIGHT_BOMB_BUSY],
			lock_on_laser);
	enemy[0]=(new CMover(eg))
		->SetObj3D(Obj3D[ENEMY])
		->SetAiming(0.3f, 0)
		->SetAutoYaw()
		->SetDamage(1, 1, enemy_crash, NULL, false, false);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->SetPos(37.5f, 0)
		->AddSpawn(enemy[0], 0, 60, -1);
	AddStage(stage, "鎖定雷射",
		"使用瞄準器來鎖定敵人後再朝敵人發射導引雷射。\n\n"
		"●雷射●\n[X]鍵／按鈕2");

	//==========================================================
	// 沿著地形飛行的飛彈
	CMover* missile_crash=(new CMover(wg))
		->SetObj3D(Obj3D[CRASH_MISSILE])
		->SetDirected(0.3f, 0.5f)
		->SetNotInherit(IH_YAW)
		->SetScale(0.5f, 0.5f, 0.1f, 0.1f)
		->SetAlpha(2, -0.04f)
		->SetNext(NULL, 50);
	CMover* missile=(new CMover(wg))
		->SetObj3D(Obj3D[MISSILE_SMALL])
		->SetAutoYaw()
		->SetDirected(0.5f, 0.1f)
		->SetGroundHit(GR_HIT, GR_ALONG)
		->SetLaser(40, -0.025f, false, Obj3D[MISSILE_TAIL_SMALL], true, true)
		->SetDamage(1, 1, missile_crash, NULL, false, false);
	myship=(new CMover(MyShipSideView))
		->SetWeapon_Shot(WP_BASIC_SHOT, missile);
	CMover* gnd_y=(new CMover(gg))
		->SetObj3D(Obj3D[GROUND_YELLOW])
		->SetDirected(0.3f, 0.5f);
	CMover* gnd0=(new CMover(sg))
		->SetPos(105, 55)
		->AddSpawn(gnd_y, 0, 170, -1);
	CMover* gnd1=(new CMover(sg))
		->SetPos(105, 63)
		->AddSpawn(gnd_y, 0, 100, -1);
	CMover* gnd2=(new CMover(sg))
		->SetPos(105, 63)
		->AddSpawn(gnd_y, 26, 100, -1);
	CMover* gnd3=(new CMover(sg))
		->SetPos(105, 71)
		->AddSpawn(gnd_y, 0, 25, -1);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(gnd0, 0, 0, 1)
		->AddSpawn(gnd1, 0, 0, 1)
		->AddSpawn(gnd2, 0, 0, 1)
		->AddSpawn(gnd3, 0, 0, 1);
	AddStage(stage, "沿著地形飛行的飛彈", 
		"會沿著牆壁或地面等地形飛行的飛彈。\n\n"
		"●飛彈●\n[X]鍵／按鈕2"
		,VIEW_SIDE);

	//==========================================================
	// 利用地形反射的子彈
	CMover* reflect_shot=(new CMover(wg))
		->SetObj3D(Obj3D[SHOT_SMALL])
		->SetAutoYaw()
		->SetDirected(0.8f, 0.15f)
		->SetGroundHit(GR_HIT, GR_REFLECT);
	myship=(new CMover(MyShipSideView))
		->SetWeapon_Shot(WP_BASIC_SHOT, reflect_shot);
	CMover* gnd4=(new CMover(sg))
		->SetPos(105, 12)
		->AddSpawn(gnd_y, 50, 100, -1);
	CMover* gnd5=(new CMover(sg))
		->SetPos(105, 12)
		->AddSpawn(gnd_y, 76, 100, -1);
	CMover* gnd6=(new CMover(sg))
		->SetPos(105, 4)
		->AddSpawn(gnd_y, 50, 25, -1);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(gnd1, 0, 0, 1)
		->AddSpawn(gnd2, 0, 0, 1)
		->AddSpawn(gnd3, 0, 0, 1)
		->AddSpawn(gnd4, 0, 0, 1)
		->AddSpawn(gnd5, 0, 0, 1)
		->AddSpawn(gnd6, 0, 0, 1);
	AddStage(stage, "利用地形反射的子彈", 
		"利用地形上下移動，行進方向得到改變的攻擊。\n\n"
		"●發射●\n[X]鍵／按鈕2"
		,VIEW_SIDE);

	//==========================================================
	// 利用地形反射的雷射
	CMover* reflect_laser=(new CMover(wg))
		->SetObj3D(Obj3D[LASER_THIN_PURPLE])
		->SetAutoYaw()
		->SetDirected(0.8f, 0.15f)
		->SetGroundHit(GR_HIT, GR_REFLECT)
		->SetLaser(40, -0.02f, true);
	myship=(new CMover(MyShipSideView))
		->SetWeapon_Shot(WP_BASIC_SHOT, reflect_laser);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(gnd1, 0, 0, 1)
		->AddSpawn(gnd2, 0, 0, 1)
		->AddSpawn(gnd3, 0, 0, 1)
		->AddSpawn(gnd4, 0, 0, 1)
		->AddSpawn(gnd5, 0, 0, 1)
		->AddSpawn(gnd6, 0, 0, 1);
	AddStage(stage, "利用地形反射的雷射", 
		"利用地形上下移動，行進方向得到改變的雷射。\n\n"
		"●雷射●\n[X]鍵／按鈕2"		
		,VIEW_SIDE);

	//==========================================================
	// 切換方向來達成全方位射擊
	CMover* turn_shot=(new CMover(wg))
		->SetObj3D(Obj3D[SHOT_SMALL])
		->SetDirected(3.0f, 0.75f)
		->SetAutoYaw()
		->SetDamage(1, 1, NULL, NULL, false, false);
	CMover* myship_crash=(new CMover(sg))
		->SetObj3D(Obj3D[CRASH_MYSHIP])
		->SetScale(0.2f, 0.2f, 0.2f, 0.2f)
		->SetAlpha(2, -0.04f)
		->SetNext(NULL, 50);
	myship=(new CMover(mg))
		->SetObj3D(Obj3D[MYSHIP])
		->SetMyShip(0, 37.5f, 90, 0.5f)
		->SetWeapon_Shot(WP_AUTO_SHOT, turn_shot)
		->SetDamage(1, 1, myship_crash, NULL, false, false)
		->SetTurnMarker(2, 30, 0.75f, Obj3D[SIGHT_BOMB_READY]);
	enemy[0]=(new CMover(eg))
		->SetPos(37.5f, 0)
		->SetObj3D(Obj3D[ENEMY])
		->SetAiming(0.3f, 0)
		->SetAutoYaw()
		->SetDamage(1, 1, enemy_crash, NULL, false, false);
	enemy[1]=(new CMover(enemy[0]))
		->SetPos(37.5f, 100);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(enemy[0], 0, 60, -1)
		->AddSpawn(enemy[1], 0, 60, -1);
	AddStage(stage, "切換方向來達成全方位射擊",
		"按住按鍵的期間使自機旋轉，使攻擊方向360度自由變換。\n\n"
		"●發射●\n[X]鍵／按鈕2\n\n"
		"●方向變換●\n[C]鍵／按鈕3");

#endif

}



