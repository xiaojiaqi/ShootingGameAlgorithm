#include <stdlib.h>

// �G�̊Ԋu
#define INTERVAL 6

// �G�̏��i�\���́j
typedef struct ENEMY_STRUCT {
	float X, Y;                 // ���݂̍��W
	float OldX[INTERVAL];       // �Â�X���W
	float OldY[INTERVAL];       // �Â�Y���W
	int Index;                  // �ł��Â����W���w���C?�f��N�X
	struct ENEMY_STRUCT* Prec;  // 1�O�̓G
} ENEMY;
// �t���s��??
void Formation(
	int num_enemy,  // �G��?
	ENEMY* enemy[]  // �G�̏��i�\���̂ւ̃|�C?�^�j
) {
	// �G�𓮂���
	int i;
for (i=0; i<num_enemy; i++) {
		ENEMY* self=enemy[i];
		ENEMY* prec=self->Prec;
		
		// ����ȊO�̓G�𓮂����F
		// 1�O�̓G�m�������Ă���Â����W�̴ӂ��C
		// �����Ƃ��Â����̂������̍��W�ɂ���B
		if (prec) {
			self->X=prec->OldX[prec->Index];
			self->Y=prec->OldY[prec->Index];
		}
		
		// ����̓G�𓮂����F
		// ��̓I��??��MoveEnemy��?�ōs�ӂƂ���B
		else {
			MoveEnemy(i);
		}
	}

	// �Â����W���L�^����F
	// �ł��Â����W���肵�����W�ŏ�?�����C
	// �C?�f��N�X���X�肷��B
	for (i=0; i<num_enemy; i++) {
		ENEMY* self=enemy[i];
		self->OldX[self->Index]=self->X;
		self->OldY[self->Index]=self->Y;
		self->Index=(self->Index+1)%INTERVAL;
	}
}
