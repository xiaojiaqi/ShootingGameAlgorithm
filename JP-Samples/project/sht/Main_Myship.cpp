#include "Main.h"


//==============================================================
// ��CShtGame���X�e�[�W�̍\�z�i���@�j
void CShtGame::MakeStages_MyShip() {
	CMover *stage;
	CMoverGroup* mg=MoverGroupManager->GetGroup(MYSHIP_GROUP);
	CMoverGroup* sg=MoverGroupManager->GetGroup(STAGE_GROUP);
	CMoverGroup* bg=MoverGroupManager->GetGroup(BULLET_GROUP);
	CMoverGroup* eg=MoverGroupManager->GetGroup(ENEMY_GROUP);
	CMoverGroup* wg=MoverGroupManager->GetGroup(WEAPON_GROUP);
	CMoverGroup* gg=MoverGroupManager->GetGroup(GROUND_GROUP);
	CMoverGroup* ig=MoverGroupManager->GetGroup(ITEM_GROUP);
	CMoverGroup* ag=MoverGroupManager->GetGroup(WATER_GROUP);
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
		->SetAiming(0.3f, 0)
		->SetAutoYaw()
		->SetDamage(1, 1, enemy_crash, NULL, false, false);

#ifndef CMAGA6

	//==========================================================
	// ���[�v�ړ�
	CMover* warp_effect=(new CMover(sg))
		->SetObj3D(Obj3D[MYSHIP])
		->SetAlpha(0.6f, -0.02f)
		->SetNext(NULL, 30);
	myship=(new CMover(MyShipTopView))
		->SetWarp(10, 20, warp_effect);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1);
	AddStage(stage, "���[�v�ړ�", 
		"���ꂽ�ꏊ�ւ̏u�Ԉړ��B\n"
		"\n"
		"�����[�v��\n"
		"�����L�[�܂��̓X�e�B�b�N�𓯂������ɑf�����Q�����");

	//==========================================================
	// �{�^���ɂ��X�s�[�h����
	myship=(new CMover(MyShipTopView))
		->SetSCButton(0.5f, 0.5f, 1.5f, 1);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1);
	AddStage(stage, "�{�^���ɂ��X�s�[�h����",
		"�{�^�����������тɎ��@�̃X�s�[�h���ω�����B\n\n"
		"���X�s�[�h���߁�\n[X]�L�[�^�{�^���Q");

	//==========================================================
	// �A�C�e���ɂ��X�s�[�h����
	CMover* sc_item0=(new CMover(ig))
		->SetObj3D(Obj3D[ITEM_YELLOW])
		->SetPos(20, 0)
		->SetDirected(0.3f, 0.25f)
		->SetRoll(0.01f)
		->SetItemEffect_Accel(0.5f);
	CMover* sc_item1=(new CMover(ig))
		->SetObj3D(Obj3D[ITEM_BLUE])
		->SetPos(55, 0)
		->SetDirected(0.3f, 0.25f)
		->SetRoll(-0.01f)
		->SetItemEffect_Accel(-0.5f);
	myship=(new CMover(MyShipTopView))
		->SetSCItem(0.5f, 1.5f);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(sc_item0, 0, 150, -1)
		->AddSpawn(sc_item1, 75, 150, -1);
	AddStage(stage, "�A�C�e���ɂ��X�s�[�h����", 
		"�A�C�e������邽�тɎ��@�̃X�s�[�h���ω�����B\n"
		"���F�̓X�s�[�h�A�b�v�C�F�̓X�s�[�h�_�E���B");

	//==========================================================
	// ���̂��鎩�@
	CMover* docking_item=(new CMover(ig))
		->SetObj3D(Obj3D[DOCKING_ITEM])
		->SetDirected(0.3f, 0.25f)
		->SetRoll(0.01f)
		->SetItemEffect_Docking(true);
	CMover* docking_enemy=(new CMover(enemy))
		->SetObj3D(Obj3D[DOCKING_ENEMY])
		->SetPos(37.5f, 0);
	CMover* docking_shot=(new CMover(shot))
		->SetDamage(1, 1, docking_item, NULL, false, false);
	myship=(new CMover(MyShipTopView))
		->SetWeapon_Shot(WP_BASIC_SHOT, docking_shot)
		->SetDocking(Obj3D[DOCKING_MYSHIP], max_shot);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(docking_enemy, 1, 250, -1);
	AddStage(stage, "���̂��鎩�@", 
		"�p�[�c���^�ԓG��j�󂵁C�p�[�c���E���ƁC���@�����������B\n\n"
		"���V���b�g��\n[X]�L�[�^�{�^���Q");

	//==========================================================
	// �n���������@
	CMover* side_shot=(new CMover(wg))
		->SetObj3D(Obj3D[SHOT_SMALL])
		->SetDirected(2.0f, 0.0f)
		->SetAutoYaw()
		->SetDamage(1, 1, NULL, NULL, false, false);
	myship=(new CMover(MyShipSideView))
		->SetObj3D(Obj3D[WALK_MYSHIP])
		->SetWeapon_Shot(WP_BASIC_SHOT, side_shot)
		->SetWalk(0, 0.2f, 0, -0.8f, 60, 2);
	CMover* air_e=(new CMover(enemy))
		->SetDirected(0.8f, 0.5f);
	CMover* air0=(new CMover(sg))
		->SetPos(100, 30)
		->AddSpawn(air_e, 0, 80, -1);
	CMover* gnd_e=(new CMover(eg))
		->SetObj3D(Obj3D[ENEMY_CANNON])
		->SetYaw(0.01f)
		->SetDirected(0.4f, 0.5f)
		->SetDamage(1, 1, enemy_crash, NULL, false, false);
	CMover* gnd0=(new CMover(sg))
		->SetPos(105, 65)
		->AddSpawn(gnd_e, 0, 170, -1);
	CMover* gnd_y=(new CMover(gg))
		->SetObj3D(Obj3D[GROUND_YELLOW])
		->SetDirected(0.4f, 0.5f);
	CMover* gnd1=(new CMover(sg))
		->SetPos(105, 71)
		->AddSpawn(gnd_y, 0, 19, -1);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(air0, 0, 0, 1)
		->AddSpawn(gnd0, 100, 0, 1)
		->AddSpawn(gnd1, 0, 0, 1);
	AddStage(stage, "�n���������@", 
		"�n����������C�W�����v�����肷�鎩�@�B\n\n"
		"���V���b�g��\n[X]�L�[�^�{�^���Q"
		"���W�����v��\n[C]�L�[�^�{�^���R"
		,VIEW_SIDE);

	//==========================================================
	// �ό`���鎩�@
	CMover* tr_effect=(new CMover(sg))
		->SetObj3D(Obj3D[BERSERK])
		->SetScale(0.5f, 0.5f, 0.1f, 0.1f)
		->SetAlpha(1, -0.08f)
		->SetNext(NULL, 10);
	CMover* tr_myship1=(new CMover(MyShipSideView));
	CMover* tr_myship2=(new CMover(MyShipSideView))
		->SetObj3D(Obj3D[WALK_MYSHIP])
		->SetMyShip(0, 50, 30, 0.5f)
		->SetWalk(0, 0.2f, 0, -0.8f, 60, 2);
	tr_myship1->SetTransform(tr_myship2, tr_effect, 1);
	tr_myship2->SetTransform(tr_myship1, tr_effect, 1);
	CMover* tr_gnd0=(new CMover(sg))
		->SetPos(105, 65)
		->AddSpawn(gnd_e, 0, 170, -1);
	CMover* tr_gnd1=(new CMover(sg))
		->SetPos(105, 71)
		->AddSpawn(gnd_y, 0, 19, -1);
	stage=(new CMover(sg))
		->AddSpawn(tr_myship1, 0, 0, 1)
		->AddSpawn(air0, 0, 0, 1)
		->AddSpawn(tr_gnd0, 100, 0, 1)
		->AddSpawn(tr_gnd1, 0, 0, 1);
	AddStage(stage, "�ό`���鎩�@", 
		"���s��ԂƔ�s��Ԃ�؂�ւ��邱�Ƃ̂ł��鎩�@�B\n\n"
		"���ό`��\n[X]�L�[�^�{�^���Q"
		"���W�����v��\n[C]�L�[�^�{�^���R"
		,VIEW_SIDE);

	//==========================================================
	// �����̈ړ�
	CMover* wat=(new CMover(ag))
		->SetObj3D(Obj3D[WATER])
		->SetDirected(0.4f, 0.5f);
	CMover* wat0=(new CMover(ag))
		->SetPos(105, 47)
		->AddSpawn(wat, 0, 19, -1);
	CMover* wat1=(new CMover(ag))
		->SetPos(105, 55)
		->AddSpawn(wat, 0, 19, -1);
	CMover* wat2=(new CMover(ag))
		->SetPos(105, 63)
		->AddSpawn(wat, 0, 19, -1);
	CMover* wave=(new CMover(sg))
		->SetObj3D(Obj3D[WAVE])
		->SetDirected(2.0f, 0.5f)
		->SetScale(2.0f, 2.0f, -0.1f, -0.1f)
		->SetAlpha(1, -0.02f)
		->SetNext(NULL, 20);
	myship=(new CMover(MyShipSideView))
		->SetUnderwater(0.1f, 42, 43, wave);
	stage=(new CMover(sg))
		->AddSpawn(myship, 200, 0, 1)
		->AddSpawn(wat0, 0, 0, 1)
		->AddSpawn(wat1, 0, 0, 1)
		->AddSpawn(wat2, 0, 0, 1)
		->AddSpawn(gnd1, 0, 0, 1);
	AddStage(stage, "�����̈ړ�", 
		"�������ړ�����Ƃ��ɂ͒x���Ȃ�C���ʂł͐����Ԃ�������",
		VIEW_SIDE);

	//==========================================================
	// �I�v�V����
	myship=(new CMover(MyShipTopView))
		->SetMyShip(0, 37.5f, 90, 0.8f)
		->SetOption(4, 10, Obj3D[OPTION]);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1);
	AddStage(stage, "�I�v�V����",
		"���@�̌�����Ă��鉇�R�B");

	//==========================================================
	// �o���A
	CMover* bullet=(new CMover(eg))
		->SetObj3D(Obj3D[BULLET_SMALL_BLUE])
		->SetAiming(0.6f, 0)
		->SetYaw(0.05f)
		->SetDamage(1, 1, NULL, NULL, false, false);
	CMover* barrier=(new CMover(wg))
		->SetObj3D(Obj3D[BARRIER])
		->SetDamage(1, 5, NULL, NULL, false, false);
	CMover* enemy_b=(new CMover(enemy))
		->SetPos(37.5f, 0)
		->AddSpawn(bullet, 0, 50, -1);
	myship=(new CMover(MyShipTopView))
		->SetBarrier(barrier, 5.0f);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(enemy_b, 0, 100, -1);
	AddStage(stage, "�o���A", 
		"�e��G��h���ł���邪�C���̃_���[�W���󂯂�Ə�������B");

#endif

}



