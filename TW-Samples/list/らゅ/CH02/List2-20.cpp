#include <stdio.h>

// �~�T�C?�̊e?����\���\����
typedef struct MISSILE_STRUCT {
	float X, Y;                   // ���W
	float VX, VY;                 // ���g
	float OldX, OldY;             // �Â����W
	float Angle;                  // ��]�p�g
	float OldAngle;               // �Â���]�p�g
	struct MISSILE_STRUCT* Prec;  // 1�O��?���ւ̃|�C?�^
	                              // �i���?���̏�?�ɂ�NULL�j
	bool IsMissile;               // �~�T�C?���Ǵӂ�
	                              // �itrue�Ȃ�~�T�C?�C
	                              //   false�Ȃ�?�j
} MISSILE_TYPE;

// �~�T�C?�̔���
void ShootMissile(
	float x, float y,   // ���˒n���̍��W
	int length          // ?�[�U�[�̒���
) {
	MISSILE_TYPE* missile;    // �~�T�C?�̍\���̂ւ̃|�C?�^
	MISSILE_TYPE* prec=NULL;  // 1�O��?�����w���|�C?�^
	
	// �~�T�C?�̊e?�������F
	// �~�T�C?�̍\���̂��m�����C���W��?��������B
	// �\���̊m���̋�̓I��??��NewMissileType��?�ōs�ӂƂ���B
	for (int i=0; i<length; i++, prec=missile) {
		missile=NewMissileType();
		missile->X=missile->OldX=x;
		missile->Y=missile->OldY=y;
		missile->Angle=missile->OldAngle=0;

		// ����?����1�O��?�����Q�Ƃ����ӂɂ��C
		// ��[?���ɂ�NULL���Q�Ƃ�����B
		missile->Prec=prec;

		// ��[?���̓~�T�C?�ɁC����?����?�ɂ���B
		missile->IsMissile=(i==0);
	}
}

