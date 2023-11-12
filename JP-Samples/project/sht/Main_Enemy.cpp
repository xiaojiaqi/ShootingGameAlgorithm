#include "Main.h"


//==============================================================
// ＜CShtGame＞ステージの構築（敵）
void CShtGame::MakeStages_Enemy() {
	CMover *stage;
	CMoverGroup* mg=MoverGroupManager->GetGroup(MYSHIP_GROUP);
	CMoverGroup* sg=MoverGroupManager->GetGroup(STAGE_GROUP);
	CMoverGroup* bg=MoverGroupManager->GetGroup(BULLET_GROUP);
	CMoverGroup* eg=MoverGroupManager->GetGroup(ENEMY_GROUP);
	CMoverGroup* wg=MoverGroupManager->GetGroup(WEAPON_GROUP);
	CMoverGroup* gg=MoverGroupManager->GetGroup(GROUND_GROUP);
	CMoverGroup* ig=MoverGroupManager->GetGroup(ITEM_GROUP);
	CMoverGroup* ag=MoverGroupManager->GetGroup(WATER_GROUP);
	CMoverGroup* rg=MoverGroupManager->GetGroup(BARRIER_GROUP);
	CMoverGroup* geg=MoverGroupManager->GetGroup(GROUND_ENEMY_GROUP);
	CMoverGroup* jog=MoverGroupManager->GetGroup(JOINT_GROUP);
	CMover *myship;

	CMover* shot=(new CMover(wg))
		->SetObj3D(Obj3D[SHOT_SMALL])
		->SetDirected(3.0f, 0.75f)
		->SetDamage(1, 1, NULL, NULL, false, false);
	CMover* max_shot=(new CMover(wg))
		->SetObj3D(Obj3D[SHOT_LARGE])
		->SetDirected(3.0f, 0.75f)
		->SetDamage(1, 1, NULL, NULL, false, false);
	CMover* enemy_crash=(new CMover(sg))
		->AddSpawn((new CMover(sg))
			->SetObj3D(Obj3D[CRASH_ENEMY])
			->SetScale(0.5f, 0.5f, 0.1f, 0.1f)
			->SetAlpha(2, -0.04f)
			->SetNext(NULL, 50)
			, 0, 0, 1);
	CMover* enemy=(new CMover(eg))
		->SetObj3D(Obj3D[ENEMY])
		->SetPos(37.5f, 0)
		->SetAiming(0.3f, 0)
		->SetAutoYaw()
		->SetDamage(1, 1, enemy_crash, NULL, false, false);
	CMover* bullet=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_BLUE])
		->SetAiming(0.6f, 0)
		->SetYaw(0.05f);

#ifndef CMAGA6

	//==========================================================
	// 破壊できる敵
	CMover* br_enemy_s=(new CMover(enemy))
		->SetPos(20, 0)
		->SetRand(0, 0.1f);
	CMover* br_enemy_h=(new CMover(enemy))
		->SetObj3D(Obj3D[ENEMY_BLUE])
		->SetPos(50, 0)
		->SetDamage(1, 50, enemy_crash, NULL, false, false)
		->SetRand(0, 0.1f);
	CMover* br_max_shot=(new CMover(max_shot))
		->SetDamage(5, 1, NULL, NULL, false, false);
	myship=(new CMover(MyShipTopView))
		->SetWeapon_Laser(WP_SHOT_AND_LASER, shot, br_max_shot, 10, 10);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(br_enemy_s, 0, 10, -1)
		->AddSpawn(br_enemy_h, 0, 10, -1);
	AddStage(stage, "破壊できる敵", 
		"耐久力が違う2種類の敵。\n\n"
		"■ショット（押しっぱなしで強化）■\n[X]キー／ボタン２");

	//==========================================================
	// 破壊できない敵
	CMover* ub_enemy0=(new CMover(enemy))
		->SetPos(20, 0)
		->SetRand(0, 0.1f)
		->SetDamage(1, 1, enemy_crash, NULL, true, false);
	CMover* ub_enemy1=(new CMover(enemy))
		->SetObj3D(Obj3D[ENEMY_BLUE])
		->SetPos(50, 0)
		->SetRand(0, 0.1f)
		->SetAlpha(0.5f, 0)
		->SetDamage(1, 50, enemy_crash, NULL, false, true);
	myship=(new CMover(MyShipTopView))
		->SetWeapon_Laser(WP_SHOT_AND_LASER, shot, br_max_shot, 10, 10);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(ub_enemy0, 0, 20, -1)
		->AddSpawn(ub_enemy1, 0, 20, -1);
	AddStage(stage, "破壊できない敵", 
		"硬くて破壊できない敵と，ショットが当たらない敵。\n\n"
		"■ショット（押しっぱなしで強化）■\n[X]キー／ボタン２");

	//==========================================================
	// 空中に現れる敵
	CMover* em_enemy=(new CMover(eg))
		->SetObj3D(Obj3D[ENEMY_REV])
		->SetDamage(1, 1, enemy_crash, NULL, false, false);		
	CMover* em_enemy_disappear=(new CMover(em_enemy))
		->SetAlpha(1, -0.05f)
		->SetNext(NULL, 20);
	CMover* em_enemy_attack=(new CMover(em_enemy))
		->AddSpawn(bullet, 0, 10, -1)
		->AddSpawn(em_enemy_disappear, 39, 0, 1)
		->SetNext(NULL, 40);
	CMover* em_enemy_appear=(new CMover(em_enemy))
		->SetAlpha(0, 0.05f)
		->SetPos(37.5f, 30)
		->SetXYRand(70, 60)
		->AddSpawn(em_enemy_attack, 19, 0, 1)
		->SetNext(NULL, 20);
	myship=(new CMover(MyShipTopView))
		->SetWeapon_Shot(WP_BASIC_SHOT, shot);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(em_enemy_appear, 0, 15, -1);
	AddStage(stage, "空中に現れる敵", 
		"空中に出現し，攻撃後に消失する敵。\n\n"
		"■ショット■\n[X]キー／ボタン２");

#endif

	//==========================================================
	// 固定砲台
	static CObject3D* fc_chip[]={
		Obj3D[CHIP0], Obj3D[CHIP1], Obj3D[CHIP2], Obj3D[CHIP3]
	}; 
	static int fc_map[]= {
		1,1,1,0,1,1,1,
		1,1,1,0,1,1,1,
		2,1,1,0,0,0,0,
		3,2,1,0,1,1,1,
		1,0,1,0,1,1,1,
		1,0,0,0,2,1,1,
		1,0,1,1,0,1,1,
		1,0,1,1,0,1,1,
		1,0,1,1,0,1,1,
		0,0,1,1,3,0,0,
		1,3,2,1,1,1,1,
		1,1,3,2,1,1,1,
		1,1,1,0,1,1,1,
	};
	CMover* fc_bg=(new CMover(sg))
		->SetBg(fc_chip, fc_map, 7, 13, 0, 0, 75, 100, 10, 10, 0, -0.3f)
		->SetZ(-50);
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
	CMover* fc_crash=(new CMover(sg))
		->SetObj3D(Obj3D[CRASH_ENEMY])
		->SetScale(0.5f, 0.5f, 0.1f, 0.1f)
		->SetDirected(0.3f, 0.25f)
		->SetAlpha(2, -0.04f)
		->SetNext(NULL, 50);
	CMover* fc_ruin=(new CMover(sg))
		->SetObj3D(Obj3D[RUIN])
		->SetDirected(0.3f, 0.25f)
		->AddSpawn(fc_crash, 0, 0, 1);
	CMover* fc_enemy=(new CMover(geg))
		->SetObj3D(Obj3D[ENEMY_CANNON])
		->SetPos(37.5f, -5)
		->SetXYRand(70, 0)
		->SetDirected(0.3f, 0.25f)
		->AddSpawn(bullet, 0, 30, -1)
		->SetDamage(1, 1, fc_ruin, NULL, false, false);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(fc_bg, 0, 0, 1)
		->AddSpawn(fc_enemy, 30, 75, -1)
		->AddSpawn(fc_enemy, 0, 120, -1);
	AddStage(stage, "固定砲台", 
		"地面と一緒にスクロールする敵。\n\n"
		"■爆撃■\n"
		"[X]キー／ボタン２");

	//==========================================================
	// 軌道を描いて飛ぶ敵
	static ORBIT or_orbit[]={
		{0, 2, 8}, {-0.7f, 1.7f, 7}, {-1.4f, 1.4f, 6}, {-1.7f, 0.7f, 5}, 
		{-2, 0, 4}, {-1.4f, -1.4f, 4}, {-0.7f, -1.7f, 3}, {0, -2, 3},
		{0.7f, -1.7f, 3}, {1.4f, -1.4f, 3}, {1.7f, -0.7f, 3}, {2, 0, 3}, 
		{1.7f, 0.7f, 4}, {1.4f, 1.4f, 4}, {0.7f, 1.7f, 5}, {0, 2, 5}, 
		{-0.7f, 1.7f, 6}, {-1.4f, 1.4f, 6}
	};
	CMover* or_enemy=(new CMover(eg))
		->SetAutoYaw()
		->SetXYRand(20, 0)
		->SetDamage(1, 1, enemy_crash, NULL, false, false);		
	CMover* or_enemy0=(new CMover(or_enemy))
		->SetObj3D(Obj3D[ENEMY])
		->SetPos(55, 0)
		->SetOrbit(or_orbit, sizeof(or_orbit)/sizeof(ORBIT), 1, 1, false);
	CMover* or_enemy1=(new CMover(or_enemy))
		->SetObj3D(Obj3D[ENEMY_BLUE])
		->SetPos(20, 0)
		->SetOrbit(or_orbit, sizeof(or_orbit)/sizeof(ORBIT), -1, 1, false);

#ifndef CMAGA6

	myship=(new CMover(MyShipTopView))
		->SetWeapon_Shot(WP_BASIC_SHOT, shot);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(or_enemy0, 0, 100, -1)
		->AddSpawn(or_enemy1, 50, 100, -1);
	AddStage(stage, "軌道を描いて飛ぶ敵", 
		"滑らかな軌道を描いて飛ぶ敵。\n\n"
		"■ショット■\n"
		"[X]キー／ボタン２");

#endif


	//==========================================================
	// 敵の編隊
	CMover* fm_enemy0=(new CMover(or_enemy0))
		->SetXYRand(0, 0);
	CMover* fm_enemy1=(new CMover(or_enemy1))
		->SetXYRand(0, 0);
	CMover* fm_gen0=(new CMover(sg))
		->AddSpawn(fm_enemy0, 0, 5, 10)
		->SetNext(NULL, 60);
	CMover* fm_gen1=(new CMover(sg))
		->AddSpawn(fm_enemy1, 0, 5, 10)
		->SetNext(NULL, 60);
	myship=(new CMover(MyShipTopView))
		->SetWeapon_Shot(WP_BASIC_SHOT, shot);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(fm_gen0, 0, 150, -1)
		->AddSpawn(fm_gen1, 75, 150, -1);
	AddStage(stage, "敵の編隊", 
		"滑らかな軌道を描いて飛ぶ敵の編隊。\n\n"
		"■ショット■\n"
		"[X]キー／ボタン２");

#ifndef CMAGA6

	//==========================================================
	// ボス
	CMover* bs_bullet0=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_BLUE])
		->SetDirected(0.7f, 0);
	CMover* bs_bullet1=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_PURPLE])
		->SetDirected(0.7f, 0);
	CMover* bs_cannon=(new CMover(geg))
		->SetObj3D(Obj3D[ENEMY_CANNON])
		->SetFollowParent()
		->SetDamage(1, 1, enemy_crash, NULL, false, false);
	CMover* bs_cannon0=(new CMover(bs_cannon))
		->SetYaw(0.01f)
		->AddSpawn(bs_bullet0, 0, 8, -1);
	CMover* bs_cannon1=(new CMover(bs_cannon))
		->SetYaw(-0.01f)
		->AddSpawn(bs_bullet1, 0, 8, -1);
	CMover* bs_crash=(new CMover(sg))
		->SetObj3D(Obj3D[CRASH_ENEMY])
		->SetScale(2, 2, 0.2f, 0.2f)
		->SetAlpha(2, -0.04f)
		->SetNext(NULL, 50);
	CMover* bs_boss1=(new CMover(sg))
		->AddSpawn(bs_cannon0, 0, 0, 1, -14, 2)
		->AddSpawn(bs_cannon1, 0, 0, 1,  -6, 2)
		->AddSpawn(bs_cannon1, 0, 0, 1,   6, 2)
		->AddSpawn(bs_cannon0, 0, 0, 1,  14, 2)
		->SetObj3D(Obj3D[BOSS1])
		->SetFollowParent()
		->SetDamage(1, 1, bs_crash, NULL, false, false);
	CMover* bs_laser=(new CMover(bg))
		->SetObj3D(Obj3D[SHOT_LARGE])
		->SetAutoYaw()
		->SetDirected(1.5f, 0.25f);
	CMover* bs_laser_gen=(new CMover(sg))
		->SetFollowParent()
		->AddSpawn(bs_laser, 1, 1, -1)
		->SetNext(NULL, 30);
	CMover* bs_laser_cannon=(new CMover(eg))
		->SetObj3D(Obj3D[BOSS_CANNON])
		->SetFollowParent()
		->SetRoll(0.01f)
		->AddSpawn(bs_laser_gen, 50, 200, -1, 0, 12)
		->SetDamage(1, 3, bs_crash, NULL, false, false);
	CMover* bs_boss2=(new CMover(sg))
		->AddSpawn(bs_laser_cannon, 0, 0, 1, 0, 5)
		->AddSpawn(bs_cannon1, 0, 0, 1,  -6, -6)
		->AddSpawn(bs_cannon1, 0, 0, 1,   6, -6)
		->AddSpawn(bs_cannon0, 0, 0, 1, -13, 10)
		->AddSpawn(bs_cannon0, 0, 0, 1,  13, 10)
		->SetObj3D(Obj3D[BOSS2])
		->SetFollowParent()
		->SetDamage(1, 1, bs_crash, NULL, false, false);
	static ORBIT bs_orbit[]={
		{-0.1f, -0.05f, 120}, 
		{ 0.1f, -0.05f, 120}, 
		{ 0.1f,  0.05f, 120}, 
		{-0.1f,  0.05f, 120}, 
	};
	CMover* bs_boss0=(new CMover(eg))
		->AddSpawn(bs_boss1, 0, 0, 1, 0, 15)
		->AddSpawn(bs_boss2, 0, 0, 1, 0, 35)
		->AddSpawn(bs_cannon0, 0, 0, 1, -20, -4)
		->AddSpawn(bs_cannon1, 0, 0, 1, -20,  4)
		->AddSpawn(bs_cannon0, 0, 0, 1,  20, -4)
		->AddSpawn(bs_cannon1, 0, 0, 1,  20,  4)
		->SetObj3D(Obj3D[BOSS0])
		->SetPos(37.5f, 25)
		->SetOrbit(bs_orbit, sizeof(bs_orbit)/sizeof(ORBIT), 1, 1, true)
		->SetDamage(1, 1, bs_crash, NULL, false, false);
	myship=(new CMover(MyShipTopView))
		->SetSightedBomb(
			0, -20, 
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
					20, 0, 1)
				->SetNext(NULL, 20)
			);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(bs_boss0, 0, 0, 1);
	AddStage(stage, "ボス",
		"多くの砲台とレーザー発射装置を備えたボス。\n"
		"艦橋を破壊すれば一撃で沈む。\n\n"
		"■爆撃■\n[X]キー／ボタン２");

#endif

	//==========================================================
	// 触手
	CMover* tt_bullet=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_BLUE])
		->SetAiming(0.6f, 0)
		->SetYaw(0.05f);
	CMover* tt_head=(new CMover(eg))
		->SetObj3D(Obj3D[BULLET_MEDIUM_BLUE])
		->SetPos(50, 50)
		->SetSimpleHoming(0.3f)
		->AddSpawn(bullet, 0, 80, -1);
	CMover* tt_body=(new CMover(eg))
		->SetObj3D(Obj3D[BULLET_MEDIUM_PURPLE]);
	CMover* tt_root=(new CMover(eg))
		->SetObj3D(Obj3D[BULLET_MEDIUM_BLUE])
		->SetPos(0, 50);
	CJointMover* tentacle=(new CJointMover(jog))
		->SetTentacle(tt_head, tt_body, tt_root, 25, 3, 50);
	myship=(new CMover(MyShipTopView));
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(tentacle, 1, 0, 1);
	AddStage(stage, "触手", "伸び縮みする触手。");

	//==========================================================
	// 多関節
	CJointMover* joint=(new CJointMover(jog))
		->SetJoint(tt_head, tt_body, tt_root, 25, 0, 0.0002f, 0.02f, 2);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(joint, 1, 0, 1);
	AddStage(stage, "多関節", "曲がるけれども伸び縮みしない関節。");

	//==========================================================
	// 撃ち返し
	CMover* rv_enemy0=(new CMover(enemy))
		->SetRand(0.1f, 0.1f)
		->SetPos(37.5f, -2)
		->SetXYRand(60, 0);
	CMover* rv_bullet=(new CMover(bullet))
		->SetAiming(1.5f, 0);
	CMover* rv_crash=(new CMover(enemy_crash))
		->AddSpawn(rv_bullet, 0, 0, 1);
	CMover* rv_enemy1=(new CMover(rv_enemy0))
		->SetDamage(1, 1, rv_crash, NULL, false, false);
	myship=(new CMover(MyShipTopView))
		->SetWeapon_Shot(WP_AUTO_SHOT, shot);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(rv_enemy0, 0, 10, -1)
		->AddSpawn(rv_enemy1, 7, 15, -1);
	AddStage(stage, "撃ち返し", 
		"倒された瞬間に敵が狙い撃ち弾を発射する。\n\n"
		"■ショット■\n"
		"[X]キー／ボタン２");
}



