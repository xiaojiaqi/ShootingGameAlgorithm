#include "Main.h"


//==============================================================
// ��CShtGame���X�e�[�W�̍\�z�i�e�j
void CShtGame::MakeStages_Bullet() {
	CMover *stage, *enemy[100], *bullet[100], *crash[100];	
	CMoverGroup* sg=MoverGroupManager->GetGroup(STAGE_GROUP);
	CMoverGroup* bg=MoverGroupManager->GetGroup(BULLET_GROUP);
	CMoverGroup* eg=MoverGroupManager->GetGroup(ENEMY_GROUP);

	//==========================================================
	// �_�������e
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
	AddStage(stage, "�_�������e", "���@�Ɍ������Ĕ�Ԓe�B");

	//==========================================================
	// �_�������e�Q
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
	AddStage(stage, "�_�������e�Q", "���x���Ⴄ�Q��ނ̑_�������e�B");
	
	//==========================================================
	// �_�������e�iDDA�j
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
	AddStage(stage, "�_�������e�iDDA�j", "DDA���g�����_�������e�B");
	
	//==========================================================
	// �_�������e�i�Œ菬���_���j
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
	AddStage(stage, "�_�������e�i�Œ菬���_���j", "�Œ菬���_�����g�����_�������e�B");
	
	//==========================================================
	// �����e
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
	AddStage(stage, "�����e", "�w�肵�������ɔ�Ԓe�B");

	//==========================================================
	// �e�[�u�����g���������e
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
	AddStage(stage, "�e�[�u�����g���������e", "�P�U�����A���x�R�̃e�[�u�����g���������e�B\n");

	//==========================================================
	// �����e�iDDA�j
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
	AddStage(stage, "�����e�iDDA�j", "DDA���g���������e�B");

	//==========================================================
	// n-way�e
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
	AddStage(stage, "n-way�e", "���ɍL����e�B");

	//==========================================================
	// �~�`�e
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
	AddStage(stage, "�~�`�e", "�~�`�ɍL����e�B");

	//==========================================================
	// �����e
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
	AddStage(stage, "�����e", "���􂷂�e�B");

	//==========================================================
	// �Ȉ՗U���e
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
	AddStage(stage, "�Ȉ՗U���e", "�P���ȗU���A���S���Y�����g�����e�B");

	//==========================================================
	// �U���e
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
	AddStage(stage, "�U���e", "�U�������܂������U���e�B");

	//==========================================================
	// �U�����[�U�[
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
	AddStage(stage, "�U�����[�U�[", "���@��ǂ������郌�[�U�[�B");

#ifndef CMAGA6

	//==========================================================
	// �U�����[�U�[�Q
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
	AddStage(stage, "�U�����[�U�[�Q", "�r���ŗU������߂Ē��i���郌�[�U�[�B");

#endif

	//==========================================================
	// �U���~�T�C��
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
	AddStage(stage, "�U���~�T�C��", "���@��ǂ�������~�T�C���B");

	//==========================================================
	// ����n-way�e
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
	AddStage(stage, "����n-way�e", "���񂾂񑬓x���オ��n-way�e�B");

	//==========================================================
	// �����U�����[�U�[
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
	AddStage(stage, "�����U�����[�U�[", "�����ƌ������J��Ԃ��U�����[�U�[�B");

	//==========================================================
	// �����e
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
	AddStage(stage, "�����e", "�d�͂Ɉ�����ė�������e�B", VIEW_SIDE);

	//==========================================================
	// �����~�T�C��
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
	AddStage(stage, "�����~�T�C��", "�d�͂Ɉ�����ė�������~�T�C���B", VIEW_SIDE);

	//==========================================================
	// ��]�e
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
	AddStage(stage, "��]�e", "���܂����_�̎��͂���]����e�B");

	//==========================================================
	// ��]�e�Q
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
	AddStage(stage, "��]�e�Q", "���a�����ɂ��񂾂�L�����]�e�B");

	//==========================================================
	// �_�������e�{��]�e
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
	AddStage(stage, "�_�������e�{��]�e", "���S�̓�����_�������e�Ɠ��������ɂ�����]�e�B");

	//==========================================================
	// �Q�����e
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
	AddStage(stage, "�Q�����e", "�Q������ɍL����e�B");

	//==========================================================
	// ��~����U���e
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
	AddStage(stage, "��~����U���e", "��~�ƈړ����J��Ԃ��U���e�B");

	//==========================================================
	// ������U�����[�U�[
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
	AddStage(stage, "������U�����[�U�[", "�ǐՂƓ��S���J��Ԃ��U�����[�U�[�B");

	//==========================================================
	// ���i����r�[��
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
	AddStage(stage, "���i����r�[��", "���܂��������ɂ܂������i�ރr�[���B");

	//==========================================================
	// ���S�n��
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_BLUE])
		->SetDirected(0.3f, 0.25f)
		->SetYaw(0.01f);
	stage=(new CMover(sg))
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->SetPos(37.5f, 0)
		->AddSpawnNWay(bullet[0], 0, 40, -1, 19, 0.02f);
	AddStage(stage, "���S�n��", "���S�n�т�����P����n-way�e�̗�B");

	//==========================================================
	// ���S�n�тQ
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
	AddStage(stage, "���S�n�тQ", "�_�������e�������Ĉ��S�n�т��Ȃ�������B");

	//==========================================================
	// ����
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_BLUE])
		->SetAiming(0.8f, 0)
		->SetYaw(0.01f);
	stage=(new CMover(sg))
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->SetPos(37.5f, 0)
		->AddSpawnNWay(bullet[0], 0, 10, -1, 5, 0.02f);
	AddStage(stage, "����", "�������g��Ȃ��P����n-way�e�B");

	//==========================================================
	// �����Q
	bullet[0]=(new CMover(bg))
		->SetObj3D(Obj3D[BULLET_SMALL_PURPLE])
		->SetAiming(0.8f, 0)
		->SetRand(0.2f, 0.05f)
		->SetYaw(0.01f);
	stage=(new CMover(sg))
		->AddSpawn(MyShipTopView, 0, 0, 1)
		->SetPos(37.5f, 0)
		->AddSpawnNWay(bullet[0], 0, 10, -1, 5, 0.02f);
	AddStage(stage, "�����Q", "�����Ƒ��x�ɗ�����������n-way�e�B");
}

