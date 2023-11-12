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

// ?�[�U�[�̔���
void ShootHomingLaser(
	float x, float y,   // ���˒n���̍��W
	int length          // ?�[�U�[�̒���
) {
	LASER_TYPE* laser;      // ?�[�U�[��\���\���̂ւ̃|�C?�^
	LASER_TYPE* prec=NULL;  // 1�O��?�����w���|�C?�^
	
	// ?�[�U�[�̊e?�������F
	// ?�[�U�[�̍\���̂��m�����C���W��?��������B
	// �\���̊m���̋�̓I��??��NewLaserType��?�ōs�ӂƂ���B
	for (int i=0; i<length; i++, prec=laser) {
		laser=NewLaserType();
		laser->X=laser->OldX=x;
		laser->Y=laser->OldY=y;
		laser->Angle=laser->OldAngle=0;

		// ����?����1�O��?�����Q�Ƃ����ӂɂ��C
		// ��[?���ɂ�NULL���Q�Ƃ�����B
		laser->Prec=prec;
	}
}

