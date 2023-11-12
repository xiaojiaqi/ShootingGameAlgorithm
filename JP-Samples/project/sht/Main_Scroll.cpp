#include "Main.h"


//==============================================================
// ＜CShtGame＞ステージの構築（スクロール）
void CShtGame::MakeStages_Scroll() {
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
	// 背景の表示
	static CObject3D* bg_chip[]={
		Obj3D[CHIP0], Obj3D[CHIP1], Obj3D[CHIP2], Obj3D[CHIP3]
	}; 
	static int bg_map[]= {
		1,1,1,0,1,1,1,1,1,1,
		1,1,1,0,1,1,1,1,1,1,
		2,1,1,0,0,0,0,0,0,0,
		3,2,1,0,1,1,1,0,1,1,
		1,0,1,0,1,1,1,0,1,1,
		1,0,0,0,2,1,1,0,1,1,
		1,0,1,1,0,1,1,3,2,1,
		1,0,1,1,0,1,1,1,0,1,
		1,0,1,1,0,1,1,1,0,1,
		0,0,1,1,3,0,0,0,0,0,
		1,3,2,1,1,1,1,1,1,1,
		1,1,3,2,1,1,1,1,1,1,
		1,1,1,0,1,1,1,1,1,1,
	};
	CMover* bg_bg=(new CMover(sg))
		->SetBg(bg_chip, bg_map, 10, 13, 12.5f, 0, 75, 100, 10, 10, 0, -0.3f)
		->SetZ(-50);
	myship=(new CMover(MyShipTopView))
		->SetWeapon_Shot(WP_BASIC_SHOT, shot);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(bg_bg, 0, 0, 1);
	AddStage(stage, "背景の表示",
		"チップを使った背景の表示とスクロール。\n\n"
		"■ショット■\n[X]キー／ボタン２");

	//==========================================================
	// 多重スクロール
	CMover* ol_star0=(new CMover(sg))
		->SetObj3D(Obj3D[STAR0])
		->SetPos(100, 37.5f)
		->SetXYRand(0, 70)
		->SetZ(-100)
		->SetDirected(0.2f, 0.5f);
	CMover* ol_star1=(new CMover(ol_star0))
		->SetDirected(0.4f, 0.5f);
	CMover* ol_star2=(new CMover(ol_star0))
		->SetDirected(0.8f, 0.5f);
	CMover* gnd_y=(new CMover(gg))
		->SetObj3D(Obj3D[GROUND_YELLOW])
		->SetDirected(0.3f, 0.5f);
	CMover* gnd1=(new CMover(sg))
		->SetPos(105, 63)
		->AddSpawn(gnd_y, 0, 100, -1);
	CMover* gnd2=(new CMover(sg))
		->SetPos(105, 63)
		->AddSpawn(gnd_y, 26, 100, -1);
	CMover* gnd3=(new CMover(sg))
		->SetPos(105, 71)
		->AddSpawn(gnd_y, 0, 25, -1);
	CMover* gnd4=(new CMover(sg))
		->SetPos(105, 12)
		->AddSpawn(gnd_y, 50, 100, -1);
	CMover* gnd5=(new CMover(sg))
		->SetPos(105, 12)
		->AddSpawn(gnd_y, 76, 100, -1);
	CMover* gnd6=(new CMover(sg))
		->SetPos(105, 4)
		->AddSpawn(gnd_y, 50, 25, -1);
	myship=(new CMover(MyShipSideView));
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(ol_star0, 0, 1, -1)
		->AddSpawn(ol_star1, 0, 1, -1)
		->AddSpawn(ol_star2, 0, 1, -1)
		->AddSpawn(gnd1, 0, 0, 1)
		->AddSpawn(gnd2, 0, 0, 1)
		->AddSpawn(gnd3, 0, 0, 1)
		->AddSpawn(gnd4, 0, 0, 1)
		->AddSpawn(gnd5, 0, 0, 1)
		->AddSpawn(gnd6, 0, 0, 1);
	AddStage(stage, "多重スクロール", 
		"当たり判定のある地面と，当たり判定のない星との重ね合わせ。"
		,VIEW_SIDE);

	//==========================================================
	// 星のスクロール
	myship=(new CMover(MyShipTopView));
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1);
	AddStage(stage, "星のスクロール",
		"ピクセル描画を使った星の表示とスクロール。");

	//==========================================================
	// 強制縦スクロール＋限定横スクロール
	myship=(new CMover(MyShipTopView))
		->SetWeapon_Shot(WP_BASIC_SHOT, shot)
		->SetLimitedScrollX();
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(bg_bg, 0, 0, 1);
	AddStage(stage, "強制縦スクロール＋限定横スクロール",
		"強制縦スクロールだが，左右には少しずつ任意スクロールする。");

	//==========================================================
	// 強制横スクロール＋任意縦スクロール
	static CObject3D* hv_chip[]={
		NULL, Obj3D[GROUND_YELLOW], Obj3D[GROUND_CYAN]
	}; 
	static int hv_map[]= {
		0,0,1,1,0,0,0,0,0,0,
		0,1,1,1,1,0,0,0,0,0,
		0,1,1,1,1,0,0,0,0,0,
		0,0,1,1,0,0,0,0,0,0,
		0,0,0,0,0,0,0,2,0,0,
		0,0,0,0,0,0,2,2,2,0,
		0,0,0,0,0,0,0,2,0,0,
		0,0,0,0,0,0,0,0,0,0,
	};
	CMover* hv_bg=(new CMover(gg))
		->SetBg(hv_chip, hv_map, 10, 8, 0, 5, 100, 75, 10, 10, 0.3f, 0)
		->SetZ(-50);
	myship=(new CMover(MyShipSideView))
		->SetFreeScrollY();
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(hv_bg, 0, 0, 1);
	AddStage(stage, "強制横スクロール＋任意縦スクロール", 
		"強制横スクロールだが，上下には自由にスクロールできる。"
		,VIEW_SIDE);

	//==========================================================
	// 回転
	CMover* rt_bg=(new CMover(sg))
		->SetBg(bg_chip, bg_map, 10, 13, 0, 0, 75, 100, 10, 10, 0, -0.5f)
		->SetBgRotate(0)
		->SetZ(-50);
	myship=(new CMover(MyShipTopView))
		->SetMyShip(0, 37.5f, 50, 0.5f)
		->SetBgRotate(0.01f);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(rt_bg, 0, 0, 1);
	AddStage(stage, "回転",
		"スティックの入力方向に画面が回転する。");

	//==========================================================
	// 高速スクロール
	CMover* hs_bg=(new CMover(sg))
		->SetBg(bg_chip, bg_map, 10, 13, 12.5f, 0, 75, 100, 10, 10, 0, -2.0f)
		->SetZ(-50);
	myship=(new CMover(MyShipTopView))
		->SetMyShip(0, 37.5f, 90, 1.0f)
		->SetGravity(0, 0.5f)
		->SetLimitedScrollX();
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(hs_bg, 0, 0, 1);
	AddStage(stage, "高速スクロール",
		"自機が下方向に力を受ける。");

	//==========================================================
	// プレイヤーによるスクロール速度の調節
	CMover* sc_bg=(new CMover(sg))
		->SetBg(bg_chip, bg_map, 10, 13, 12.5f, 0, 75, 100, 10, 10, 0, -0.3f)
		->SetZ(-50);
	myship=(new CMover(MyShipTopView))
		->SetLimitedScrollX()
		->SetControlScrollY(0, 100, -2.0f, -0.2f);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(sc_bg, 0, 0, 1);
	AddStage(stage, "プレイヤーによるスクロール速度の調節",
		"画面上方にいるほどスクロールが速くなる。");

#endif

}



