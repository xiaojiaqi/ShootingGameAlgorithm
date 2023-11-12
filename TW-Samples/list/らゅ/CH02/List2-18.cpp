#include <stdio.h>

// ?�[�U�[�̊e?����\���\����
typedef struct LASER_STRUCT {
	float X, Y;                 // ���W
	float VX, VY;               // ���g
	float OldX, OldY;           // �Â����W
	float Angle;                // ��]�p�g
	float OldAngle;             // �Â���]�p�g
	struct LASER_STRUCT* Prec;  // 1�O��?���ւ̃|�C?�^
	                            // �i���?���̏�?�ɂ�NULL�j
} LASER_TYPE;


// ?�[�U�[�𓮂�����?
void MoveHomingLaser(
	LASER_TYPE* laser  // ?�[�U�[�̐��?���܂��͔���1?��
) {
	// ��[?���̏�?�F
	// �U���e�̓����Ɠ����B
	// �U���̋�̓I��??��MoveHoming��?�ōs�ӂƂ���B
	if (laser->Prec==NULL) {
		MoveHoming(laser);
	}

	// ��[?���ȊO�̏�?�F
	// 1�O��?����ǂ�������B
	// �Â����W�ƌÂ���]�p�g���R�s�[����B
	else {
		laser->X=laser->Prec->OldX;
		laser->Y=laser->Prec->OldY;
		laser->Angle=laser->Prec->OldAngle;
	}
}
