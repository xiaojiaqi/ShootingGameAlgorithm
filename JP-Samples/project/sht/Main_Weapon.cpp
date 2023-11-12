#include "Main.h"


//==============================================================
// ＜CShtGame＞ステージの構築（武器）
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
	// 基本のショット操作
	myship=(new CMover(MyShipTopView))
		->SetWeapon_Shot(WP_BASIC_SHOT, shot);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1);
	AddStage(stage, "基本のショット操作", 
		"ボタンを1回押すごとに1発出るショット。\n\n"
		"■ショット■\n[X]キー／ボタン２");

	//==========================================================
	// 連射
	myship=(new CMover(MyShipTopView))
		->SetWeapon_Shot(WP_AUTO_SHOT, shot);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1);
	AddStage(stage, "連射",
		"ボタン押しっぱなしで連続的に出るショット。\n\n"
		"■ショット■\n[X]キー／ボタン２");

	//==========================================================
	// 溜め撃ち
	myship=(new CMover(MyShipTopView))
		->SetWeapon_PowerShot(
			WP_POWER_SHOT, shot, big_shot, max_shot, 
			Obj3D[POWER_EFFECT], Obj3D[MAX_EFFECT],
			30, 120, 0);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1);
	AddStage(stage, "溜め撃ち",
		"ボタン押しっぱなしでエネルギーを溜めて撃つショット。\n"
		"溜めには2段階ある。\n\n"
		"■ショット■\n[X]キー／ボタン２");

	//==========================================================
	// セミオート連射
	myship=(new CMover(MyShipTopView))
		->SetWeapon_PowerShot(
			WP_SEMI_AUTO_SHOT, shot, big_shot, max_shot, 
			Obj3D[POWER_EFFECT], Obj3D[MAX_EFFECT],
			15, 120, 15);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1);
	AddStage(stage, "セミオート連射", 
		"ボタンを適度に連打すると通常のショットになり，\n"
		"押しっぱなしにすると溜め撃ちになる。\n\n"
		"■ショット／溜め撃ち■\n[X]キー／ボタン２");

	//==========================================================
	// ボタンを離して溜める溜め撃ち
	myship=(new CMover(MyShipTopView))
		->SetWeapon_PowerShot(
			WP_POWER_SHOT_RELEASED, shot, big_shot, max_shot, 
			Obj3D[POWER_EFFECT], Obj3D[MAX_EFFECT],
			30, 120, 0);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1);
	AddStage(stage, "ボタンを離して溜める溜め撃ち",
		"ボタンを離しているとエネルギーが溜まり，\n"
		"押すとショットが出る。\n\n"
		"■ショット■\n[X]キー／ボタン２");

	//==========================================================
	// 連射とレーザーの共存
	myship=(new CMover(MyShipTopView))
		->SetWeapon_Laser(WP_SHOT_AND_LASER, shot, laser, 15, 15);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1);
	AddStage(stage, "連射とレーザーの共存",
		"ボタンを適度に連打すると通常のショットになり，\n"
		"押しっぱなしにするとレーザーになる。\n\n"
		"■ショット／レーザー■\n[X]キー／ボタン２");

	//==========================================================
	// ロックショット
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
	AddStage(stage, "ロックショット",
		"ボタンを適度に連打すると通常のショットになり，\n"
		"押しっぱなしにすると敵を追うロックショットになる。\n\n"
		"■ショット／ロックショット■\n[X]キー／ボタン２");

	//==========================================================
	// コマンドショット
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
	AddStage(stage, "コマンドショット", 
		"スティック操作とボタン操作の組み合わせで特別なショットが出る。\n\n"
		"■コマンドショット１■\n下，右下，右，[X]キー／ボタン２\n\n"
		"■コマンドショット２■\n右，下，右下，[X]キー／ボタン２"
		,VIEW_SIDE);

	//==========================================================
	// 照準を使った爆撃
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
	AddStage(stage, "照準を使った爆撃",
		"照準の位置に爆弾を落とす。\n\n"
		"■爆撃■\n[X]キー／ボタン２");

	//==========================================================
	// ロックオンレーザー
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
	AddStage(stage, "ロックオンレーザー",
		"照準でロックした敵に誘導レーザーを放つ。\n\n"
		"■レーザー■\n[X]キー／ボタン２");

	//==========================================================
	// 地形に沿って飛ぶミサイル
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
	AddStage(stage, "地形に沿って飛ぶミサイル", 
		"地形の起伏に沿って上下の動きを変えるミサイル。\n\n"
		"■ミサイル■\n[X]キー／ボタン２"
		,VIEW_SIDE);

	//==========================================================
	// 地形で反射するショット
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
	AddStage(stage, "地形で反射するショット", 
		"地形に当たると上下の移動方向が反転するショット。\n\n"
		"■ショット■\n[X]キー／ボタン２"
		,VIEW_SIDE);

	//==========================================================
	// 地形で反射するレーザー
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
	AddStage(stage, "地形で反射するレーザー", 
		"地形に当たると上下の移動方向が反転するレーザー。\n\n"
		"■レーザー■\n[X]キー／ボタン２"		
		,VIEW_SIDE);

	//==========================================================
	// 方向切り替えによる全方位射撃
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
	AddStage(stage, "方向切り替えによる全方位射撃",
		"ボタンを押している間，照準の周りで自機が向きを変える。\n\n"
		"■ショット■\n[X]キー／ボタン２\n\n"
		"■方向切り替え■\n[C]キー／ボタン３");

#endif

}



