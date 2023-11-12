#include "Main.h"


//==============================================================
// ��CShtGame���X�e�[�W�̍\�z�i�X�N���[���j
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
	// �w�i�̕\��
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
	AddStage(stage, "�w�i�̕\��",
		"�`�b�v���g�����w�i�̕\���ƃX�N���[���B\n\n"
		"���V���b�g��\n[X]�L�[�^�{�^���Q");

	//==========================================================
	// ���d�X�N���[��
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
	AddStage(stage, "���d�X�N���[��", 
		"�����蔻��̂���n�ʂƁC�����蔻��̂Ȃ����Ƃ̏d�ˍ��킹�B"
		,VIEW_SIDE);

	//==========================================================
	// ���̃X�N���[��
	myship=(new CMover(MyShipTopView));
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1);
	AddStage(stage, "���̃X�N���[��",
		"�s�N�Z���`����g�������̕\���ƃX�N���[���B");

	//==========================================================
	// �����c�X�N���[���{���艡�X�N���[��
	myship=(new CMover(MyShipTopView))
		->SetWeapon_Shot(WP_BASIC_SHOT, shot)
		->SetLimitedScrollX();
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(bg_bg, 0, 0, 1);
	AddStage(stage, "�����c�X�N���[���{���艡�X�N���[��",
		"�����c�X�N���[�������C���E�ɂ͏������C�ӃX�N���[������B");

	//==========================================================
	// �������X�N���[���{�C�ӏc�X�N���[��
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
	AddStage(stage, "�������X�N���[���{�C�ӏc�X�N���[��", 
		"�������X�N���[�������C�㉺�ɂ͎��R�ɃX�N���[���ł���B"
		,VIEW_SIDE);

	//==========================================================
	// ��]
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
	AddStage(stage, "��]",
		"�X�e�B�b�N�̓��͕����ɉ�ʂ���]����B");

	//==========================================================
	// �����X�N���[��
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
	AddStage(stage, "�����X�N���[��",
		"���@���������ɗ͂��󂯂�B");

	//==========================================================
	// �v���C���[�ɂ��X�N���[�����x�̒���
	CMover* sc_bg=(new CMover(sg))
		->SetBg(bg_chip, bg_map, 10, 13, 12.5f, 0, 75, 100, 10, 10, 0, -0.3f)
		->SetZ(-50);
	myship=(new CMover(MyShipTopView))
		->SetLimitedScrollX()
		->SetControlScrollY(0, 100, -2.0f, -0.2f);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1)
		->AddSpawn(sc_bg, 0, 0, 1);
	AddStage(stage, "�v���C���[�ɂ��X�N���[�����x�̒���",
		"��ʏ���ɂ���قǃX�N���[���������Ȃ�B");

#endif

}



