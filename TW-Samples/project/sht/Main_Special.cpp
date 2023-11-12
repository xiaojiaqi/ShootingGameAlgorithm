#include "Main.h"


//==============================================================
// ＜CShtGame＞關卡的構築（特殊攻擊）
void CShtGame::MakeStages_Special() {
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
	// 炸彈
	CMover* bomb_bullet=(new CMover(eg))
		->SetObj3D(Obj3D[BULLET_SMALL_BLUE])
		->SetAiming(0.6f, 0)
		->SetYaw(0.05f)
		->SetDamage(1, 1, NULL, NULL, false, false);
	CMover* bomb_enemy=(new CMover(enemy))
		->AddSpawn(bomb_bullet, 0, 50, -1);
	CMover* bomb_crash=(new CMover(wg))
		->SetObj3D(Obj3D[CRASH_MISSILE])
		->SetScale(8, 8, 0.1f, 0.1f)
		->SetAlpha(2, -0.02f)
		->SetNext(NULL, 200);
	CMover* bomb=(new CMover(wg))
		->SetObj3D(Obj3D[MISSILE_SMALL])
		->SetDirected(1.0f, 0.75f)
		->SetDamage(0, 1, NULL, NULL, false, false)
		->AddSpawn(bomb_crash, 40, 0, 1)
		->SetNext(NULL, 40);
	myship=(new CMover(MyShipTopView))
		->SetWeapon_Shot(WP_BASIC_SHOT, bomb);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(bomb_enemy, 0, 100, -1);
	AddStage(stage, "炸彈",
		"發射一段時間才爆炸的炸彈。\n自機變成無敵。\n\n"
		"●炸彈●\n[X]鍵／按鈕2");

	//==========================================================
	// 近身攻擊
	CMover* punch=(new CMover(wg))
		->SetObj3D(Obj3D[PUNCH])
		->SetAlpha(0.2f, 0.03f);
	myship=(new CMover(MyShipTopView))
		->SetPunch(punch, 1, 60);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(bomb_enemy, 0, 100, -1);
	AddStage(stage, "近身攻擊",
		"按下按鍵後只一段時間可出現近身攻擊。\n\n"
		"●飛拳●\n[X]鍵／按鈕2");

	//==========================================================
	// 誘爆
	CMover* ie_crash=(new CMover(wg))
		->SetObj3D(Obj3D[CRASH_ENEMY])
		->SetScale(0.5f, 0.5f, 0.1f, 0.1f)
		->SetAlpha(2, -0.04f)
		->SetNext(NULL, 50);
	CMover* ie_enemy=(new CMover(eg))
		->SetObj3D(Obj3D[ENEMY])
		->SetAiming(0.3f, 0)
		->SetAutoYaw()
		->SetDamage(1, 1, ie_crash, NULL, false, false);
	CMover* ie_enemy0=(new CMover(ie_enemy))->SetPos(37.5f, 0);
	CMover* ie_enemy1=(new CMover(ie_enemy))->SetPos(0, 20);
	CMover* ie_enemy2=(new CMover(ie_enemy))->SetPos(75, 20);
	myship=(new CMover(MyShipTopView))
		->SetWeapon_Shot(WP_BASIC_SHOT, shot);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(ie_enemy0, 0, 60, -1)
		->AddSpawn(ie_enemy1, 20, 60, -1)
		->AddSpawn(ie_enemy2, 40, 60, -1);
	AddStage(stage, "誘爆",
		"敵人的爆風對另外的敵人帶來損傷。\n\n"
		"●發射●\n[X]鍵／按鈕2");

	//==========================================================
	// 利用物品的特殊攻擊
	CMover* sa_item0=(new CMover(ig))
		->SetObj3D(Obj3D[ITEM_YELLOW])
		->SetPos(37.5f, 0)
		->SetDirected(0.3f, 0.25f)
		->SetRoll(0.01f)
		->SetItemEffect_SA(true);
	CMover* sa_effect=(new CMover(sg))
		->SetObj3D(Obj3D[BERSERK])
		->SetRoll(0.01f);
	myship=(new CMover(MyShipTopView))
		->SetWeapon_Shot(WP_AUTO_SHOT, shot)
		->SetSAItem(max_shot, sa_effect, 300, 60);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(sa_item0, 0, 150, -1);
	AddStage(stage, "利用物品的特殊攻擊",
		"取物品的話只一定時間能發揮強力特殊攻擊。\n\n"
		"●發射●\n[X]鍵／按鈕2");

	//==========================================================
	// 無敵狀態
	CMover* inv_bullet=(new CMover(eg))
		->SetObj3D(Obj3D[BULLET_SMALL_BLUE])
		->SetAiming(0.6f, 0)
		->SetYaw(0.05f)
		->SetDamage(1, 1, NULL, NULL, false, false);
	CMover* inv_enemy=(new CMover(enemy))
		->AddSpawn(inv_bullet, 0, 50, -1);
	myship=(new CMover(MyShipTopView))
		->SetDamage(1, 1, NULL, NULL, true, false);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(inv_enemy, 0, 60, -1);
	AddStage(stage, "無敵狀態",
		"變成不會受到敵機傷害的狀態。");

	//==========================================================
	// 狂暴化狀態
	CMover* bs_item=(new CMover(ig))
		->SetObj3D(Obj3D[SHOT_SMALL])
		->SetDirected(3.0f, 0.75f);
	CMover* bs_myship2=(new CMover(mg))
		->SetObj3D(Obj3D[MYSHIP2])
		->SetPos(37.5f, 60)
		->AddSpawn(bs_item, 0, 5, -1);
	CMover* bs_shot=(new CMover(wg))
		->SetObj3D(Obj3D[SHOT_LARGE])
		->SetDirected(3.0f, 0)
		->SetAutoYaw()
		->SetRand(1, 1)
		->SetDamage(1, 1, NULL, NULL, false, false);
	CMover* bs_effect=(new CMover(sg))
		->SetObj3D(Obj3D[BERSERK])
		->SetRoll(0.04f)
		->AddSpawn(bs_shot, 0, 1, -1)
		->AddSpawn(bs_shot, 0, 1, -1);
	myship=(new CMover(MyShipTopView))
		->SetBerserk(bs_effect, 10, 300, 60, 200)
		->SetWeapon_Shot(WP_BASIC_SHOT, shot);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(bs_myship2, 0, 0, 1);
	AddStage(stage, "狂暴化狀態",
		"利用特別的操作或物品來讓自機維持在一定時間內能力大增。\n"
		"可向全方位發射強力子彈亂射。");

	//==========================================================
	// 抓住友機投擲
	CMover* tfs_shot=(new CMover(wg))
		->SetObj3D(Obj3D[SHOT_SMALL])
		->SetDirected(3.0f, 0.75f)
		->SetAutoYaw();
	CHit* tfs_hit=new CHit(-6, 6, -6, 6);
	CMover* tfs_myship2=(new CMover(mg))
		->SetMyShip(1, 37.5f, 60, 0.5f)
		->SetObj3D(Obj3D[MYSHIP2])
		->AddSpawn(tfs_shot, 0, 5, -1)
		->SetThrow(1, tfs_hit, -1.0f, -2.0f, 0.1f, 300);
	myship=(new CMover(MyShipTopView))
		->SetThrow(1, tfs_hit, -1.0f, -2.0f, 0.1f, 300);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(tfs_myship2, 0, 0, 1);
	AddStage(stage, "抓住友機投擲",
		"友機靠近時按下按鍵，就可以將友機抓住後投擲出去進行攻擊。\n\n"
		"●投擲●\n[X]鍵／按鈕2");

	//==========================================================
	// 俘虜敵機後投擲
	CMover* te_enemy=(new CMover(enemy));
	CMover* te_crash=(new CMover(wg))
		->SetObj3D(Obj3D[CRASH_ENEMY])
		->SetScale(0.5f, 0.5f, 0.1f, 0.1f)
		->SetAlpha(2, -0.04f)
		->SetNext(NULL, 50);
	CMover* te_shot=(new CMover(wg))
		->SetObj3D(Obj3D[ENEMY])
		->SetDirected(2.0f, 0.75f)
		->SetRoll(0.05f)
		->SetDamage(1, 1, te_crash, NULL, false, false);
	myship=(new CMover(MyShipTopView))
		->SetArm(2, Obj3D[BARRIER], Obj3D[BULLET_SMALL_BLUE], 2.0f, 20, 10, 5)
		->SetWeapon_Shot(WP_BASIC_SHOT, te_shot);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(te_enemy, 0, 60, -1);
	AddStage(stage, "俘虜敵機後投擲",
		"用手臂抓住敵機，並用按鈕操作將敵機丟出去的攻擊。\n\n"
		"●投擲●\n[X]鍵／按鈕2\n\n"
		"●手臂●\n[C]鍵／按鈕3");

	//==========================================================
	// 把捉住敵機變成友機
	CMover* ce_enemy=(new CMover(enemy))
		->AddSpawn(bullet, 0, 50, -1);
	CMover* ce_shot=(new CMover(rg))
		->SetObj3D(Obj3D[ENEMY])
		->SetRoll(0.02f)
		->AddSpawn(shot, 0, 5, -1)
		->SetDamage(1, 10, enemy_crash, NULL, false, false);
	myship=(new CMover(MyShipTopView))
		->SetArm(2, Obj3D[BARRIER], Obj3D[BULLET_SMALL_BLUE], 2.0f, 20, 10, 5)
		->SetWeapon_Shot(WP_BASIC_SHOT, ce_shot);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(ce_enemy, 0, 60, -1);
	AddStage(stage, "把捉住敵機變成友機",
		"用手臂或光束把敵機捉住後變成友機，用來別的按鍵來攻擊。\n\n"
		"●放出敵機●\n[X]鍵／按鈕2\n\n"
		"●手臂●\n[C]鍵／按鈕3");
	
	//==========================================================
	// 利用取回被敵機俘虜的自機來提昇能量
	CMover* cp_beam=(new CMover(bg))
		->SetObj3D(Obj3D[BARRIER])
		->SetScale(0.5f, 0.1f, 0.1f, 0.05f)
		->SetDirected(1.0f, 0.25f)
		->SetAlpha(1, -0.02f)
		->SetNext(NULL, 30);
	CMover* cp_enemy=(new CMover(eg))
		->SetObj3D(Obj3D[ENEMY_REV])
		->SetCaptor(cp_beam);
	CMover* cp_enemy_crash=(new CMover(sg))
		->SetObj3D(Obj3D[CRASH_ENEMY])
		->SetScale(0.2f, 0.2f, 0.2f, 0.2f)
		->SetAlpha(2, -0.04f)
		->AddSpawn(cp_enemy, 50, 0, 1)
		->SetNext(NULL, 50);
	cp_enemy
		->SetDamage(1, 1, cp_enemy_crash, NULL, false, false);
	myship=(new CMover(MyShipTopView))
		->SetWeapon_Shot(WP_BASIC_SHOT, shot)
		->SetCaptee();
	CMover* cp_myship_crash=(new CMover(sg))
		->SetObj3D(Obj3D[CRASH_MYSHIP])
		->SetScale(0.2f, 0.2f, 0.2f, 0.2f)
		->SetAlpha(2, -0.04f)
		->AddSpawn(myship, 50, 0, 1)
		->SetNext(NULL, 50);
	myship
		->SetDamage(1, 1, cp_myship_crash, NULL, false, false);
	stage=(new CMover(sg))
		->SetPos(37.5f, 30)
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(cp_enemy, 0, 0, 1);
	AddStage(stage, "利用取回被敵機俘虜的自機來提昇能量",
		"自機與光束接觸則判定被敵機捕捉，\n"
		"破壞捉住自機的敵機就可以將自機奪回，變成自機2聯合攻擊。");

	//==========================================================
	// 接近友機來強化射擊威力
	CMover* rf1_myship=(new CMover(mg))
		->SetMyShip(1, 37.5f, 60, 0.5f)
		->SetObj3D(Obj3D[MYSHIP2]);
	CMover* rf1_shot=(new CMover(wg))
		->SetObj3D(Obj3D[SHOT_LARGE])
		->SetDirected(3.0f, 0.75f)
		->SetAutoYaw()
		->SetDamage(1, 1, NULL, NULL, false, false);
	CHit* rf1_hit=new CHit(-4, 4, -4, 4);
	myship=(new CMover(MyShipTopView))
		->SetRFShot(0, rf1_shot, rf1_hit)
		->SetWeapon_Shot(WP_AUTO_SHOT, shot);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(rf1_myship, 0, 0, 1);
	AddStage(stage, "接近友機來強化射擊威力",
		"接近友機則射擊威力會變得比平常強大。\n\n"
		"●發射●\n[X]鍵／按鈕2");
	
	//==========================================================
	// 有友機在的方向，射擊子彈威力較強
	myship=(new CMover(MyShipTopView))
		->SetRFShot(1, rf1_shot, rf1_hit)
		->SetWeapon_Shot(WP_AUTO_SHOT, shot);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(rf1_myship, 0, 0, 1);
	AddStage(stage, "有友機在的方向，射擊子彈威力較強",
		"有友機在的方向，射出子彈威力較強\n"
		"依友機與自機的位置關係，來改變射擊方向。\n\n"
		"●發射●\n[X]鍵／按鈕2");
	
	//==========================================================
	// 強化射擊到友機的子彈
	CMover* rf3_myship=(new CMover(mg))
		->SetMyShip(1, 37.5f, 60, 0.5f)
		->SetRFShot(2, rf1_shot, rf1_hit)
		->SetObj3D(Obj3D[MYSHIP2]);
	myship=(new CMover(MyShipTopView))
		->SetWeapon_Shot(WP_AUTO_SHOT, shot);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(rf3_myship, 0, 0, 1);
	AddStage(stage, "強化射擊到友機的子彈",
		"射出的子彈接觸友機會變成更具威力的子彈攻擊。\n\n"
		"●發射●\n[X]鍵／按鈕2");

#endif

	//==========================================================
	// 改變自機顏色來吸收敵彈
	CMover** sc_effect=new CMover*[2];
	sc_effect[0]=sc_effect[1]=(new CMover(sg))
		->SetObj3D(Obj3D[BERSERK])
		->SetScale(0.5f, 0.5f, 0.1f, 0.1f)
		->SetAlpha(1, -0.08f)
		->SetNext(NULL, 10);
	CMover* sc_crash1=(new CMover(sg))
		->SetObj3D(Obj3D[BULLET_SMALL_ORANGE])
		->SetScale(1, 1, 0.01f, 0.01f)
		->SetAlpha(1, -0.1f)
		->SetNext(NULL, 10);
	CMover* sc_crash2=(new CMover(sg))
		->SetObj3D(Obj3D[BULLET_SMALL_GREEN])
		->SetScale(1, 1, 0.01f, 0.01f)
		->SetAlpha(1, -0.1f)
		->SetNext(NULL, 10);
	CMover* sc_bullet1=(new CMover(bullet))
		->SetObj3D(Obj3D[BULLET_SMALL_ORANGE])
		->SetColor(1)
		->SetPos(20, 0)
		->SetRand(0.2f, 0.2f)
		->SetDamage(1, 1, sc_crash1, NULL, false, false);
	CMover* sc_bullet2=(new CMover(bullet))
		->SetObj3D(Obj3D[BULLET_SMALL_GREEN])
		->SetColor(2)
		->SetPos(55, 0)
		->SetRand(0.2f, 0.2f)
		->SetDamage(1, 1, sc_crash2, NULL, false, false);
	CMover** sc_shot=new CMover*[2];
	sc_shot[0]=(new CMover(shot))
		->SetColor(1)
		->SetObj3D(Obj3D[SHOT_SMALL_ORANGE]);
	sc_shot[1]=(new CMover(shot))
		->SetColor(2)
		->SetObj3D(Obj3D[SHOT_SMALL_GREEN]);
	CHit* sc_hit=new CHit(-4, 4, -4, 4);
	CObject3D** sc_obj3d=new CObject3D*[2];
	sc_obj3d[0]=Obj3D[MYSHIP];
	sc_obj3d[1]=Obj3D[MYSHIP2];
	myship=(new CMover(MyShipTopView))
		->SetColor(1)
		->SetChangeColor(2, 2, sc_obj3d, sc_shot, sc_effect, sc_hit)
		->SetWeapon_Shot(WP_AUTO_SHOT, sc_shot[0]);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(sc_bullet1, 0, 1, -1)
		->AddSpawn(sc_bullet2, 0, 1, -1);
	AddStage(stage, "改變自機顏色來吸收敵彈", 
		"吸收和自機相同顏色的敵彈特殊攻擊。\n"
		"發射也和自機顏色。\n\n"
		"●發射●\n"
		"[X]鍵／按鈕2\n\n"
		"●改變顏色●\n"
		"[C]鍵／按鈕3");

	//==========================================================
	// 將敵彈反射回去
	CMover* rf_enemy0=(new CMover(enemy))
		->SetPos(20, 0)
		->SetDamage(1, 10, enemy_crash, NULL, false, false)
		->AddSpawn(bullet, 0, 10, -1);
	CMover* rf_enemy1=(new CMover(enemy))
		->SetPos(55, 0)
		->SetDamage(1, 10, enemy_crash, NULL, false, false)
		->AddSpawn(bullet, 0, 10, -1);
	CMover* rf_shot=(new CMover(wg))
		->SetObj3D(Obj3D[SHOT_MEDIUM])
		->SetAiming(3.0f, 0)
		->SetAutoYaw()
		->SetTarget(TG_RANDOM_ENEMY, 0, shot)
		->SetDamage(1, 1, NULL, NULL, false, false);
	CMover* reflect=(new CMover(sg))
		->SetObj3D(Obj3D[BERSERK]);
	myship=(new CMover(MyShipTopView))
		->SetReflect(1, reflect, rf_shot);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(rf_enemy0, 0, 50, -1)
		->AddSpawn(rf_enemy1, 25, 50, -1);
	AddStage(stage, "將敵彈反射回去",
		"開防護罩將敵彈反射回去的特殊攻擊。\n\n"
		"●防護罩●\n"
		"[X]鍵／按鈕2");

#ifndef CMAGA6

	//==========================================================
	// 使自機和敵機的雷射相撞
	CMover* lc_crash=(new CMover(wg))
		->SetObj3D(Obj3D[CRASH_MISSILE])
		->SetScale(12, 12, 0.2f, 0.2f)
		->SetAlpha(1, -0.05f)
		->SetNext(NULL, 20);
	CMover* lc_crash_small=(new CMover(sg))
		->SetObj3D(Obj3D[CRASH_MISSILE])
		->SetScale(4, 4, 0.2f, 0.2f)
		->SetAlpha(1, -0.05f)
		->SetNext(NULL, 20);
	CMover* lc_shot0=(new CMover(wg))
		->SetObj3D(Obj3D[SHOT_LARGE])
		->SetDirected(3.0f, 0.75f)
		->SetAutoYaw()
		->SetDamage(1, 1, lc_crash_small, NULL, false, false)
		->SetCollision(20, lc_crash);
	CMover* lc_shot1=(new CMover(eg))
		->SetObj3D(Obj3D[SHOT_LARGE])
		->SetPos(37.5f, 0)
		->SetDirected(3.0f, 0.25f)
		->SetAutoYaw()
		->SetDamage(1, 1, NULL, NULL, false, false);
	myship=(new CMover(MyShipTopView))
		->SetWeapon_Shot(WP_AUTO_SHOT, lc_shot0);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(lc_shot1, 0, 1, -1);
	AddStage(stage, "使自機和敵機的雷射相撞",
		"讓自機雷射從正面去碰撞敵機的雷射，來產生更強力攻擊。\n\n"
		"●雷射●\n[X]鍵／按鈕2");

	//==========================================================
	// 讓自機去「削」敵彈來增加等級
	CMover* gb_bullet=(new CMover(bullet))
		->SetPos(37.5f, 0)
		->SetRand(0.2f, 0.2f);
	CMover* gb_effect=(new CMover(sg))
		->SetObj3D(Obj3D[BULLET_SMALL_PURPLE])
		->SetScale(1.4f, 1.4f, -0.1f, -0.1f)
		->SetAlpha(1, -0.1f)
		->SetNext(NULL, 10);
	CMover* gb_field=(new CMover(wg))
		->SetObj3D(Obj3D[BERSERK])
		->SetFollowParent()
		->SetGraze(gb_effect)
		->SetDamage(1, 1, NULL, NULL, true, false);
	myship=(new CMover(MyShipTopView))
		->AddSpawn(gb_field, 0, 0, 1);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(gb_bullet, 0, 1, -1);
	AddStage(stage, "讓自機去「削」敵彈來增加等級",
		"讓自機和敵彈靠近到一個不會被打死的極近距離就是「削」敵彈。");

#endif

	//==========================================================
	// 讓敵彈和敵機的速度減慢
	CMover* sl_bullet=(new CMover(bullet))
		->SetRand(0.1f, 0.1f);
	CMover* sl_enemy=(new CMover(enemy))
		->SetRand(0.1f, 0.1f)
		->AddSpawn(sl_bullet, 0, 8, -1);
	myship=(new CMover(MyShipTopView))
		->SetSlow(1, -1)
		->SetQuick(2, 1);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(sl_enemy, 0, 50, -1);
	AddStage(stage, "讓敵彈和敵機的速度減慢", 
		"按下按鈕來變化敵彈和敵機的速度。\n\n"
		"●減慢●\n"
		"[X]鍵／按鈕2\n\n"
		"●加快●\n"
		"[C]鍵／按鈕3"
		);

#ifndef CMAGA6

	//==========================================================
	// 可自由移動的瞄準器
	CMover* ms1_sight=(new CMover(sg))
		->SetObj3D(Obj3D[SIGHT_BOMB_READY]);
	CMover* ms1_shot=(new CMover(wg))
		->SetObj3D(Obj3D[SHOT_LARGE])
		->SetDirected(3.0f, 0.75f)
		->SetDamage(1, 1, NULL, NULL, false, false);
	CMover* ms1_attack=(new CMover(sg))
		->SetPos(37.5f, 50)
		->SetObj3D(Obj3D[SIGHT_BOMB_TARGET])
		->AddSpawn(ms1_shot, 0, 1, -1)
		->SetNext(NULL, 60);
	CMover* ms1_enemy=(new CMover(enemy))
		->SetRand(0.1f, 0.1f);
	myship=(new CMover(MyShipTopView))
		->SetMovableSightB(1, 0, -10, 1.0f, ms1_sight, ms1_attack);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(ms1_enemy, 0, 50, -1);
	AddStage(stage, "可自由移動的瞄準器",
		"按住按鍵時可自由移動瞄準器，\n"
		"放開按鈕時就會在瞄準器所在位置發射強力攻擊。\n\n"
		"●移動瞄準器●\n[X]鍵／按鈕2");

	//==========================================================
	// 同時操作自機和瞄準器
	CMover* ms2_sight=(new CMover(sg))
		->SetObj3D(Obj3D[SIGHT_BOMB_READY]);
	CMover* ms2_shot=(new CMover(wg))
		->SetObj3D(Obj3D[SHOT_MEDIUM])
		->SetAiming(3.0f, 0)
		->SetAutoYaw()
		->SetDamage(1, 1, NULL, NULL, false, false);
	myship=(new CMover(MyShipTopView))
		->SetMovableSightS(0, -20, 1.0f, ms2_sight)
		->SetWeapon_Shot(WP_AUTO_SHOT, ms2_shot);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(ms1_enemy, 0, 50, -1);
	AddStage(stage, "同時操作自機和瞄準器",
		"自機和瞄準器可同操移動操作。\n"
		"自機會往瞄準器的方向發射攻擊。\n\n"
		"●移動瞄準器●\n[E][D][S][F]鍵\n\n"
		"●發射●\n[X]鍵／按鈕2"
		);

#endif

}



