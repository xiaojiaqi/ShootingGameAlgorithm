#include "Mover.h"
#include "Hit.h"
#include "..\LibGame\Input.h"
#include <assert.h>




//==============================================================
// �o�g���l�{��

// �@�몺�o�g
void CMover::Shot() {

	// �ܮz���A
	if (Valid.Berserk && Berserk.State!=BS_NORMAL) return;
	
	// �����C��
	if (Valid.ChangeColor) {
		New(ChangeColor.Shot[Color-1]);
	}

	// ���u
	if (Valid.Arm) {
		if (Arm.NumStock<=0) return;
		Arm.NumStock--;
		CMover* model=Weapon.Shot;
		CObject3D* obj3d=model->Obj3D;
		model->Obj3D=Arm.Stock[Arm.NumStock];
		New(model);
		model->Obj3D=obj3d;
	} else

	// �o�g�������j��
	if (Valid.RFShot) {
		CMoverGroup* mg=GetGroup(MYSHIP_GROUP);
		CMover *mover;
		CHit hit=*RFShot.Hit;
		hit.SetPos(X, Y);
		if (mover=mg->FirstHit(&hit)) {
			do {
				if (mover!=this) {
					switch (RFShot.Mode) {
						case 0:
							New(RFShot.Shot);
							return;
						case 1:
							CMover model=*RFShot.Shot;
							model.Angle=
								atan2(X-mover->X, mover->Y-Y)/D3DX_PI/2+0.25f;
							New(&model);
							return;
					}
				}
			} while (mover=mg->NextHit(&hit));
			New(Weapon.Shot);
		}
	} else

	// �ۥѲ��ʪ��˷Ǿ�
	if (Valid.MovableSightS && MovableSightS.SightMover) {
		CMover* sight=MovableSightS.SightMover;
		CMover model=*Weapon.Shot;
		model.Valid.Target=true;
		model.Target.Type=TG_MOVER;
		model.Target.Mover=sight;
		New(&model);
	} else

	// �X��
	if (Valid.Docking && Docking.Docked) {
		New(Docking.Shot);
	} else

	// �̪��~���j��
	if (Valid.SAItem && SAItem.EffectMover) {
		New(SAItem.ShotModel);
	} else

	// ���`
	{
		New(Weapon.Shot);
		if (Valid.Captee && Captee.Doubled) {
			CMover* mover=New(Weapon.Shot);
			mover->X+=10;
		}
	}
}


// �������
void CMover::BigShot(int power) {
	New(Weapon.BigShot);
}


// �̤j��q���������
void CMover::MaxShot() {
	New(Weapon.MaxShot);
}




//==============================================================
// �򥻪��g���ާ@
void CMover::BasicShot(
	bool button,       // ���������s���A
	bool& prev_button  // �W�����s���A
) {
	// �o�g�l�u�G
	// �W�������U���s�A�u�������Q����ɡA
	// �o�g�l�u�C
	// �o�g�ɪ��ӳ��B�z�Hshot��ƨӰ���C
	if (!prev_button && button) Shot();
	
	// �x�s�������s�����A
	prev_button=button;
}


//==============================================================
// �s��g��
void CMover::AutoShot(
	bool button  // ���s�����A�]���U�ɬ�true�^
) {
	//�o�g�l�u�G
	//���U���s�N�o�g�l�u�C
	//�o�g���ԲӳB�z�O�Hshot��ƨӰ���
	if (button) Shot();
}


//==============================================================
// ����g��
void CMover::PowerShot(
	bool button,    // ���s�����A�]�Q����ɬ�true�^
	int min_power,  // �g�X�l�u�һݪ��̧C��q
	int max_power,  // �̰���q
	int& power      // �ֿn��q
) {
	//���s����ɡG
	//�W�[�ֿn��q�C
	if (button && power<max_power) power++;
	
	//��}���s�ɡG
	//��q�W�n>0�ɡA�N�o�g�l�u�A�ֿn��q��_��0�C
	if (!button && power>0) {
		
		//�̰���q�ɡG
		//�o�g�S���l�u�C
		//���骺�B�z�O�H���MaxShot�Ӱ���C
		if (power==max_power) MaxShot(); else
		
		//�̧C��q�H�W�A���F��̰���q�ɡG
		//�o�g�P��q�ֿn�ȩҹ������j�O�l�u�C
		//���骺�B�z�O�HBigShot��ƨӰ���C
		if (min_power<=power) BigShot(power);
		
		//�ֿn��q��_��0
		power=0;
	}
}


//==============================================================
// �s��g���P����g���@�s
void CMover::SemiAutoShot(
	bool button,    // ���s�����A�]�Q����ɬ�true�^
	int min_power,  // �ֿn��q���̤p��
	int max_power,  // �ֿn��q���̤j��
	int max_gauge,  // �s��g���p�q���̤j��
	int& power,     // �ֿn��q
	int& gauge      // �s��g����q
) {
	// ������s��
	if (button) {
		
		//�ֿn��q�����ɡG
		//�o�g���q�l�u�C
		if (power<min_power) Shot();
	
		//�W�[�ֿn��q�A�ϳs��g���p�q���̤j
		if (power<max_power) power++;
		gauge=max_gauge;
	}
	
	//��}���s�ɡG
	else {
		
		//�ֿn��q�����ɡG
		//�o�g����u�G
		//��q���̤j�ɡA�o�g�S��l�u�C
		if (min_power<=power) {
			if (power==max_power) MaxShot(); 
				else BigShot(power);
			gauge=0;
		}
		
		//�s��g���p�q��>0�ɡG
		//�o�g���q�l�u�A�ϳs��g���p�q��-1�C 
		if (gauge>0) {
			Shot();
			gauge--;
		}

		//�ϲֿn��q��0
		power=0;
	}
}


//==============================================================
// ��}���s�o�g����u
void CMover::PowerShotReleased(
	bool button,    // ���s�����A�]�Q����ɬ�true�^
	int min_power,  // �o�g�l�u���̧C��q
	int max_power,  // �̰���q
	int& power      // �ֿn��q
) {
	//��}���s�ɡG
	//�W�[�ֿn��q�C
	if (!button && power<max_power) power++;
	
	//���U���s�ɡG
	//�ֿn��q>0�ɵo�g�l�u�A�ֿn��q��_��0�C
	if (button && power>0) {
		
		//�̤j��q�ɡG
		//�o�g�S�O�l�u�C
		//����B�z�O�HMaxShot��ƨӰ���C
		if (power==max_power) MaxShot(); else
		
		//�̧C��q�H�W�A�������̰���q�ɡG
		//�o�g�P�ֿn��q�ȹ������j�O�l�u�C
		//����B�z�O�HBigShot��ƨӰ���C
		if (min_power<=power) BigShot(power);
		
		//�ֿn��q��_��0
		power=0;
	}
}


//==============================================================
// ���O�g��
void CMover::CommandShot(const CInputState* is) {
	int& index=Weapon.Cmd.HistIndex;
	int* hist=Weapon.Cmd.Hist;
	COMMAND_LIST* list=Weapon.Cmd.List;

	// �N��J���{�O���U��
	hist[index]=
		(is->Up?CMD_UP:0)|
		(is->Down?CMD_DOWN:0)|
		(is->Left?CMD_LEFT:0)|
		(is->Right?CMD_RIGHT:0)|
		(is->Button[0]?CMD_BUTTON0:0)|
		(is->Button[1]?CMD_BUTTON1:0)|
		(is->Button[2]?CMD_BUTTON2:0)|
		(is->Button[3]?CMD_BUTTON3:0);

	// �P�w�U���O�O�_��J
	int c, j, i;
	for (c=0; c<list->NumCommand; c++) {
		COMMAND& cmd=list->Command[c];
		
		// �T�{���O����J
		for (i=0, j=cmd.Length-1; j>=0; j--) {
			for (; i<cmd.Limit; i++) {
				if (hist[(index-i+NUM_CMD_HIST)%NUM_CMD_HIST]==
					cmd.Input[j]) break;
			}
			if (i==cmd.Limit) break;
		}
		
		// �����T�{���O����J�G
		// ������O�g���A�M�����{�C
		if (j==-1) {
			CMover* mover=Group->GetManager()->GetGroup(WEAPON_GROUP)->New();
			if (mover) mover->Init(cmd.Model, this);
			for (i=0; i<NUM_CMD_HIST; i++) hist[i]=CMD_NONE;
		}
	}
	
	// ��s�O������m
	index=(index+1)%NUM_CMD_HIST;
}


//==============================================================
// �s��g���P�p�g�@�s
void CMover::ShotAndLaser(
	bool button,    // ���s�����A�]���U�ɬ�true�^
	int min_power,  // �ֿn��q���̤p��
	int max_gauge,  // �s��g���p�q���̤j��
	int& power,     // �ֿn��q
	int& gauge      // �s��g����q
) {
	// ���U���s��
	if (button) {
		
		//�ֿn��q�����ɡG
		//�W�[�ֿn��q�A�ϳs��g���p�q���̤j�A
		//�o�g�l�u�C����B�z�O�HShot��ƨӰ���C
		if (power<min_power) {
			power++;
			gauge=max_gauge;
			Shot();
		}
	
		//�ֿn��q�����ɡG
		//�ϳs��g���p�q��0�A�o�g�p�g�C
		else {
			gauge=0;
			CMover* mover=Group->GetManager()->GetGroup(WEAPON_GROUP)->New();
			if (mover) mover->Init(Weapon.Laser, this);
		}
	}
	
	//��}���s�ɡG
	else {
		
		//�s��g���p�q��>0�ɡG 
		//�o�g�@��l�u�A�N�s��g���p�q��-1�C
		if (gauge>0) {
			Shot();
			gauge--;
		}

		//�ϲֿn��q��0�C
		power=0;
	}
}


//==============================================================
// ��w�g��
void CMover::LockShot(
	bool button,     // ���s�����A�]���U�ɬ�true�^
	int min_power,   // �ֿn��q���̤p��
	int max_gauge,   // �s��g���p�q���̤j��
	int& power,      // �ֿn��q
	int& gauge       // �s��g����q
) {
	//���U���s��
	if (button) {
		
		//�ֿn��q�����ɡG
		//�W�[�ֿn��q�B�ϳs��g���p�q���̤j�A
		//�o�g�l�u�C����B�z�O�HShot��ƨӰ���C
		if (power<min_power) {
			power++;
			gauge=max_gauge;
			Shot();
		}
	
		//�ֿn��q�R���ɡG
		//�ϳs��g���p�q��0�A������w�g���C
		else {
			gauge=0;
			
			//��w�g���G
			//�l�ܼľ��ɡA�˷ǼĤH�C
			//�]�P�u�µۦ۾����Ӫ��l�u�v��z�ۦP�^
			//���l�ܼľ��ɡA�¦۾�������V�o�g�l�u�C
			//�]�P�u�¦ۥѤ�V�o�g�l�u�v�ۦP�^
			CMover* mover=Group->GetManager()->GetGroup(WEAPON_GROUP)->New();
			mover->Init(Weapon.Laser, this);
		}
	}
	
	//��}���s�ɡG
	else {
		
		//�s��g���p�q��>0�ɡG
		//�o�g�@��l�u�A�s��g���p�q��-1�C
		if (gauge>0) {
			Shot();
			gauge--;
		}

		//�ϲֿn��q��0 
		power=0;

		// �Ѱ���w
		ClearLockedEnemy();
	}
}




