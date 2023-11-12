#include "Main.h"


//==============================================================
// ��CShtGame�����d���c�v�]�l�u�^
void CShtGame::MakeStages_Bullet() {
	CMover *stage, *enemy[100], *bullet[100], *crash[100];	
	CMoverGroup* sg=MoverGroupManager->GetGroup(STAGE_GROUP);
	CMoverGroup* bg=MoverGroupManager->GetGroup(BULLET_GROUP);
	CMoverGroup* eg=MoverGroupManager->GetGroup(ENEMY_GROUP);

	//==========================================================
	// �˷Ǽu
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
	AddStage(stage, "�˷Ǽu", "�V�۾��o�g���l�u�C");

	//==========================================================
	// �˷Ǽu2
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
	AddStage(stage, "�˷Ǽu2", "�t�פ��P����ت��˷Ǽu�C");
	
	//==========================================================
	// �˷Ǽu�]DDA�^
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
	AddStage(stage, "�˷Ǽu�]DDA�^", "�ϥ�DDA���˷Ǽu�C");
	
	//==========================================================
	// �˷Ǽu�]�T�w�p���I�^
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
	AddStage(stage, "�˷Ǽu�]�T�w�p���I�^", "�ϥΩT�w�p���I���˷Ǽu�C");
	
	//==========================================================
	// ��V�u
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
	AddStage(stage, "��V�u", "�«��w��V���檺�l�u");

	//==========================================================
	// �ϥ�Table����V�u
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
	AddStage(stage, "�ϥ�Table����V�u", "�H�t��3�¦V16�Ӥ�V�g�X���l�u�C\n");

	//==========================================================
	// ��V�u�]DDA�^
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
	AddStage(stage, "��V�u�]DDA�^", "�ϥ�DDA����V�u�C");

	//==========================================================
	// n-way�u
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
	AddStage(stage, "n-way�u", "�H���ήg�X���l�u�C");

	//==========================================================
	// ��μu
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
	AddStage(stage, "��μu", "������δ��g�X�h���l�u�C");

	//==========================================================
	// �����u
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
	AddStage(stage, "�����u", "�|�����n�X�Ӫ��l�u�g�X�C");

	//==========================================================
	// ²�����ɼu
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
	AddStage(stage, "²�����ɼu", "�ϥΤF��»��ɺt��k���l�u�C");

	//==========================================================
	// ���ɼu
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
	AddStage(stage, "���ɼu", "�|�l�ܦ۾������ɼu�C");

	//==========================================================
	// ���ɹp�g
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
	AddStage(stage, "���ɹp�g", "�|�l�ܦ۾����p�g�C");

#ifndef CMAGA6

	//==========================================================
	// ���ɹp�g2
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
	AddStage(stage, "���ɹp�g2", "�|�b�~������ɥH���u�e�i���p�g�C");

#endif

	//==========================================================
	// �ɤޭ��u
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
	AddStage(stage, "�ɤޭ��u", "�|�l�ܦ۾������u�C");

	//==========================================================
	// �[�tn-way�u
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
	AddStage(stage, "�[�tn-way�u", "�g�X��|���[�t��n-way�u�C");

	//==========================================================
	// �[�t���ɹp�g
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
	AddStage(stage, "�[�t���ɹp�g", "�|���ƥ[�t�M��t�����ɹp�g�C");

	//==========================================================
	// �Y���u
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
	AddStage(stage, "�Y���u", "�|�̭��O�Y�����l�u�C", VIEW_SIDE);

	//==========================================================
	// �Y�����u
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
	AddStage(stage, "�Y�����u", "�|�̭��O�Y�������u�C", VIEW_SIDE);

	//==========================================================
	// ����u
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
	AddStage(stage, "����u", "��¶�ۤ����I�P����઺�l�u�C");

	//==========================================================
	// ����u2
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
	AddStage(stage, "����u2", "�̤��P�b�|���઺�l�u�C");

	//==========================================================
	// �˷Ǽu+����u
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
	AddStage(stage, "�˷Ǽu+����u", "�¦۾���V�g�Ӫ��l�u�P����u�ҲզX�Ӧ��C");

	//==========================================================
	// �x���u
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
	AddStage(stage, "�x���u", "�|�e�x�������}���l�u�C");

	//==========================================================
	// �|������ɼu
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
	AddStage(stage, "�|������ɼu", "�|�b�~������M��S���ʰl�V�۾����l�u�C");

	//==========================================================
	// �|�k�������ɹp�g
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
	AddStage(stage, "�|�k�������ɹp�g", "�|���ưl�ܻP�k�������ɹp�g�C");

	//==========================================================
	// ���i����
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
	AddStage(stage, "���i����", "�ª��u��V�e�i���ʤj�����C");

	//==========================================================
	// �w���a�a
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_BLUE])
		->SetDirected(0.3f, 0.25f)
		->SetYaw(0.01f);
	stage=(new CMover(sg))
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->SetPos(37.5f, 0)
		->AddSpawnNWay(bullet[0], 0, 40, -1, 19, 0.02f);
	AddStage(stage, "�w���a�a", "�b�w���a�a�����n-way�u�d�ҡC");

	//==========================================================
	// �w���a�a2
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
	AddStage(stage, "�w���a�a2", "�[�W�˷Ǽu���w���a�a���d�ҡC");

	//==========================================================
	// �ü�
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_BLUE])
		->SetAiming(0.8f, 0)
		->SetYaw(0.01f);
	stage=(new CMover(sg))
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->SetPos(37.5f, 0)
		->AddSpawnNWay(bullet[0], 0, 10, -1, 5, 0.02f);
	AddStage(stage, "�ü�", "�ϥζüƪ����n-way�u�C");

	//==========================================================
	// �ü�2
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_PURPLE])
		->SetAiming(0.8f, 0)
		->SetRand(0.2f, 0.05f)
		->SetYaw(0.01f);
	stage=(new CMover(sg))
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->SetPos(37.5f, 0)
		->AddSpawnNWay(bullet[0], 0, 10, -1, 5, 0.02f);
	AddStage(stage, "�ü�2", "��V�P�t�ץH�üƧe�{��n-way�u�C");
}

