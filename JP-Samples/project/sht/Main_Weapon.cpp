#include "Main.h"


//==============================================================
// ��CShtGame���X�e�[�W�̍\�z�i����j
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
	// ��{�̃V���b�g����
	myship=(new CMover(MyShipTopView))
		->SetWeapon_Shot(WP_BASIC_SHOT, shot);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1);
	AddStage(stage, "��{�̃V���b�g����", 
		"�{�^����1�񉟂����Ƃ�1���o��V���b�g�B\n\n"
		"���V���b�g��\n[X]�L�[�^�{�^���Q");

	//==========================================================
	// �A��
	myship=(new CMover(MyShipTopView))
		->SetWeapon_Shot(WP_AUTO_SHOT, shot);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1);
	AddStage(stage, "�A��",
		"�{�^���������ςȂ��ŘA���I�ɏo��V���b�g�B\n\n"
		"���V���b�g��\n[X]�L�[�^�{�^���Q");

	//==========================================================
	// ���ߌ���
	myship=(new CMover(MyShipTopView))
		->SetWeapon_PowerShot(
			WP_POWER_SHOT, shot, big_shot, max_shot, 
			Obj3D[POWER_EFFECT], Obj3D[MAX_EFFECT],
			30, 120, 0);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1);
	AddStage(stage, "���ߌ���",
		"�{�^���������ςȂ��ŃG�l���M�[�𗭂߂Č��V���b�g�B\n"
		"���߂ɂ�2�i�K����B\n\n"
		"���V���b�g��\n[X]�L�[�^�{�^���Q");

	//==========================================================
	// �Z�~�I�[�g�A��
	myship=(new CMover(MyShipTopView))
		->SetWeapon_PowerShot(
			WP_SEMI_AUTO_SHOT, shot, big_shot, max_shot, 
			Obj3D[POWER_EFFECT], Obj3D[MAX_EFFECT],
			15, 120, 15);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1);
	AddStage(stage, "�Z�~�I�[�g�A��", 
		"�{�^����K�x�ɘA�ł���ƒʏ�̃V���b�g�ɂȂ�C\n"
		"�������ςȂ��ɂ���Ɨ��ߌ����ɂȂ�B\n\n"
		"���V���b�g�^���ߌ�����\n[X]�L�[�^�{�^���Q");

	//==========================================================
	// �{�^���𗣂��ė��߂闭�ߌ���
	myship=(new CMover(MyShipTopView))
		->SetWeapon_PowerShot(
			WP_POWER_SHOT_RELEASED, shot, big_shot, max_shot, 
			Obj3D[POWER_EFFECT], Obj3D[MAX_EFFECT],
			30, 120, 0);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1);
	AddStage(stage, "�{�^���𗣂��ė��߂闭�ߌ���",
		"�{�^���𗣂��Ă���ƃG�l���M�[�����܂�C\n"
		"�����ƃV���b�g���o��B\n\n"
		"���V���b�g��\n[X]�L�[�^�{�^���Q");

	//==========================================================
	// �A�˂ƃ��[�U�[�̋���
	myship=(new CMover(MyShipTopView))
		->SetWeapon_Laser(WP_SHOT_AND_LASER, shot, laser, 15, 15);
	stage=(new CMover(sg))
		->AddSpawn(myship, 0, 0, 1);
	AddStage(stage, "�A�˂ƃ��[�U�[�̋���",
		"�{�^����K�x�ɘA�ł���ƒʏ�̃V���b�g�ɂȂ�C\n"
		"�������ςȂ��ɂ���ƃ��[�U�[�ɂȂ�B\n\n"
		"���V���b�g�^���[�U�[��\n[X]�L�[�^�{�^���Q");

	//==========================================================
	// ���b�N�V���b�g
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
	AddStage(stage, "���b�N�V���b�g",
		"�{�^����K�x�ɘA�ł���ƒʏ�̃V���b�g�ɂȂ�C\n"
		"�������ςȂ��ɂ���ƓG��ǂ����b�N�V���b�g�ɂȂ�B\n\n"
		"���V���b�g�^���b�N�V���b�g��\n[X]�L�[�^�{�^���Q");

	//==========================================================
	// �R�}���h�V���b�g
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
	AddStage(stage, "�R�}���h�V���b�g", 
		"�X�e�B�b�N����ƃ{�^������̑g�ݍ��킹�œ��ʂȃV���b�g���o��B\n\n"
		"���R�}���h�V���b�g�P��\n���C�E���C�E�C[X]�L�[�^�{�^���Q\n\n"
		"���R�}���h�V���b�g�Q��\n�E�C���C�E���C[X]�L�[�^�{�^���Q"
		,VIEW_SIDE);

	//==========================================================
	// �Ə����g��������
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
	AddStage(stage, "�Ə����g��������",
		"�Ə��̈ʒu�ɔ��e�𗎂Ƃ��B\n\n"
		"��������\n[X]�L�[�^�{�^���Q");

	//==========================================================
	// ���b�N�I�����[�U�[
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
	AddStage(stage, "���b�N�I�����[�U�[",
		"�Ə��Ń��b�N�����G�ɗU�����[�U�[����B\n\n"
		"�����[�U�[��\n[X]�L�[�^�{�^���Q");

	//==========================================================
	// �n�`�ɉ����Ĕ�ԃ~�T�C��
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
	AddStage(stage, "�n�`�ɉ����Ĕ�ԃ~�T�C��", 
		"�n�`�̋N���ɉ����ď㉺�̓�����ς���~�T�C���B\n\n"
		"���~�T�C����\n[X]�L�[�^�{�^���Q"
		,VIEW_SIDE);

	//==========================================================
	// �n�`�Ŕ��˂���V���b�g
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
	AddStage(stage, "�n�`�Ŕ��˂���V���b�g", 
		"�n�`�ɓ�����Ə㉺�̈ړ����������]����V���b�g�B\n\n"
		"���V���b�g��\n[X]�L�[�^�{�^���Q"
		,VIEW_SIDE);

	//==========================================================
	// �n�`�Ŕ��˂��郌�[�U�[
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
	AddStage(stage, "�n�`�Ŕ��˂��郌�[�U�[", 
		"�n�`�ɓ�����Ə㉺�̈ړ����������]���郌�[�U�[�B\n\n"
		"�����[�U�[��\n[X]�L�[�^�{�^���Q"		
		,VIEW_SIDE);

	//==========================================================
	// �����؂�ւ��ɂ��S���ʎˌ�
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
	AddStage(stage, "�����؂�ւ��ɂ��S���ʎˌ�",
		"�{�^���������Ă���ԁC�Ə��̎���Ŏ��@��������ς���B\n\n"
		"���V���b�g��\n[X]�L�[�^�{�^���Q\n\n"
		"�������؂�ւ���\n[C]�L�[�^�{�^���R");

#endif

}



