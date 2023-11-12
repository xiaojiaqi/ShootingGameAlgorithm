#include "Main.h"


//==============================================================
// ＜CShtGame＞ステージの構築（特殊攻撃）
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
	// ボム
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
	AddStage(stage, "ボム",
		"爆発するまで少しだけ時間の掛かるボム。\n自機は無敵にはならない。\n\n"
		"■ボム■\n[X]キー／ボタン２");

	//==========================================================
	// 近接攻撃
	CMover* punch=(new CMover(wg))
		->SetObj3D(Obj3D[PUNCH])
		->SetAlpha(0.2f, 0.03f);
	myship=(new CMover(MyShipTopView))
		->SetPunch(punch, 1, 60);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(bomb_enemy, 0, 100, -1);
	AddStage(stage, "パンチ",
		"ボタンを押すと一定時間だけ近接攻撃が出る。\n\n"
		"■パンチ■\n[X]キー／ボタン２");

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
		"敵の爆風が別の敵にダメージを与える。\n\n"
		"■ショット■\n[X]キー／ボタン２");

	//==========================================================
	// アイテムによる特殊攻撃
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
	AddStage(stage, "アイテムによる特殊攻撃",
		"アイテムを取ると一定時間だけ強いショットが撃てる。\n\n"
		"■ショット■\n[X]キー／ボタン２");

	//==========================================================
	// 無敵状態
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
	AddStage(stage, "無敵状態",
		"敵にも弾にも負けない無敵状態。");

	//==========================================================
	// バーサーク
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
	AddStage(stage, "バーサーク",
		"味方のショットを浴びるとバーサーク状態になる。\n"
		"バーサーク状態では全方向にショットを乱射する。");

	//==========================================================
	// 味方をつかんで投げる
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
	AddStage(stage, "味方をつかんで投げる",
		"味方近くでボタンを押すと味方を投げることができる。\n\n"
		"■投げる■\n[X]キー／ボタン２");

	//==========================================================
	// 敵をつかんで投げる
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
	AddStage(stage, "敵をつかんで投げる",
		"敵をアームで捕らえて，別のボタンで投げる。\n\n"
		"■投げる■\n[X]キー／ボタン２\n\n"
		"■アーム■\n[C]キー／ボタン３");

	//==========================================================
	// 敵をつかまえて味方にする
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
	AddStage(stage, "敵をつかまえて味方にする",
		"敵をアームで捕らえて，別のボタンで攻撃させる。\n\n"
		"■敵を出す■\n[X]キー／ボタン２\n\n"
		"■アーム■\n[C]キー／ボタン３");
	
	//==========================================================
	// 敵につかまった自機を取り返してパワーアップする
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
	AddStage(stage, "敵につかまった自機を取り返してパワーアップする",
		"敵のビームを浴びると自機が捕獲される。\n"
		"捕獲された状態で敵を破壊すると，自機が2連装になる。");

	//==========================================================
	// 味方に接近してショットを強化する
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
	AddStage(stage, "味方に接近してショットを強化する",
		"味方に接近すると強力なショットが撃てる。\n\n"
		"■ショット■\n[X]キー／ボタン２");
	
	//==========================================================
	// 味方がいる方向に強いショットを撃つ
	myship=(new CMover(MyShipTopView))
		->SetRFShot(1, rf1_shot, rf1_hit)
		->SetWeapon_Shot(WP_AUTO_SHOT, shot);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(rf1_myship, 0, 0, 1);
	AddStage(stage, "味方がいる方向に強いショットを撃つ",
		"味方に接近すると強力なショットが撃てる。\n"
		"味方との位置関係によってショットの方向が変わる。\n\n"
		"■ショット■\n[X]キー／ボタン２");
	
	//==========================================================
	// 味方に当てたショットを強化する
	CMover* rf3_myship=(new CMover(mg))
		->SetMyShip(1, 37.5f, 60, 0.5f)
		->SetRFShot(2, rf1_shot, rf1_hit)
		->SetObj3D(Obj3D[MYSHIP2]);
	myship=(new CMover(MyShipTopView))
		->SetWeapon_Shot(WP_AUTO_SHOT, shot);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(rf3_myship, 0, 0, 1);
	AddStage(stage, "味方に当てたショットを強化する",
		"味方にショットを当てると強力なショットに変わる。\n\n"
		"■ショット■\n[X]キー／ボタン２");

#endif

	//==========================================================
	// 自機の色を切り替えて弾を吸収する
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
	AddStage(stage, "自機の色を切り替えて弾を吸収する", 
		"自機と同じ色の弾を吸収する特殊攻撃。\n"
		"ショットも自機と同じ色になる。\n\n"
		"■ショット■\n"
		"[X]キー／ボタン２\n\n"
		"■色の切り替え■\n"
		"[C]キー／ボタン３");

	//==========================================================
	// 敵の弾をショットとして跳ね返す
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
	AddStage(stage, "敵の弾をショットとして跳ね返す",
		"バリアに当たった弾を敵に跳ね返す特殊攻撃。\n\n"
		"■バリア■\n"
		"[X]キー／ボタン２");

#ifndef CMAGA6

	//==========================================================
	// レーザー同士をぶつける
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
	AddStage(stage, "レーザー同士をぶつける",
		"レーザー同士を衝突させると強力な攻撃が発生する。\n\n"
		"■レーザー■\n[X]キー／ボタン２");

	//==========================================================
	// 敵弾に自機をかすらせる
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
	AddStage(stage, "敵弾に自機をかすらせる",
		"自機のすぐ近くを敵弾が通過すると「かすり」と判定される。");

#endif

	//==========================================================
	// 弾や敵の動きをスローにする
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
	AddStage(stage, "弾や敵の動きをスローにする", 
		"ボタン操作で弾や敵の動きを変化させる。\n\n"
		"■スロー■\n"
		"[X]キー／ボタン２\n\n"
		"■クイック■\n"
		"[C]キー／ボタン３"
		);

#ifndef CMAGA6

	//==========================================================
	// 自由に動かせる照準
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
	AddStage(stage, "自由に動かせる照準",
		"ボタン押しっぱなしで照準を動かすことができる。\n"
		"ボタンを離すと照準の位置に攻撃が発生する。\n\n"
		"■照準移動■\n[X]キー／ボタン２");

	//==========================================================
	// 自機と照準を同時に動かす
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
	AddStage(stage, "自機と照準を同時に動かす",
		"自機と照準とを別のキーで動かす。\n"
		"ショットは照準に向かって発射される。\n\n"
		"■照準移動■\n[E][D][S][F]キー\n\n"
		"■ショット■\n[X]キー／ボタン２"
		);

#endif

}



