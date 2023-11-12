// ?�[�U�[�̊e?����\���\����
typedef struct LASER_STRUCT {
	float X, Y;                 // ������W
	float W, H;                 // ?��?��
	float VX, VY;               // ���g
	float OldX, OldY;           // �Â����W
	struct LASER_STRUCT* Prec;  // 1�O��?��
	                            // �i���?���̏�?�ɂ�NULL�j
} LASER_TYPE;

// ?�[�U�[�𓮂�����?
void MoveReflectLaser(
	LASER_TYPE* laser,         // ?�[�U�[��1��?��
	float gx0[], float gy0[],  // �n�`�̍�����W
	float gx1[], float gy1[],  // �n�`�̅������W
	int num_ground             // �n�`��?
) {
	// ��[?���̏�?�F
	// �n�`�Ŕ��˂���V?��g��??�Ɠ����B
	if (!laser->Prec) {

		// �n�`�Ƃ�?���蔻�]??�F
		// ��[?����?�����؂ɐi�߂����W(X, Y+VY)�ɂ��āC
		// �n�`��?���邩�Ǵӂ��𔻃]����B
		// �n�`��?��������?�ɂ́C?�����؂̑��g����ɂ��āC
		// ?�[�v���甲����B
		for (int i=0; i<num_ground; i++) {
			if (gx0[i]<laser->X+laser->W &&
				laser->X<gx1[i] && 
				gy0[i]<laser->Y+laser->W+laser->VY &&
				laser->Y+laser->VY<gy1[i]
			) {
				laser->VX=-laser->VX;
				break;
			}
		}

		// ��[?����i�߂�
		laser->X+=laser->VX;
		laser->Y+=laser->VY;
	}
	
	// ��[?���ȊO�̏�?�F
	// 1�O��?����ǂ�������B
	// 1�O��?���̌Â����W�ֈړ�����B
	else {
		laser->X=laser->Prec->OldX;
		laser->Y=laser->Prec->OldY;
	}
}

