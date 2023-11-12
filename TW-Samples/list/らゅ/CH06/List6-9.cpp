#include <stdlib.h>

// �G�̏��i�\���́j
typedef struct ENEMY_STRUCT {
	float X, Y;                 // ���݂̍��W
	float OldX[INTERVAL];       // �Â�X���W
	float OldY[INTERVAL];       // �Â�Y���W
	int Index;                  // �ł��Â����W���w���C?�f��N�X
	struct ENEMY_STRUCT* Prec;  // 1�O�̓G
} ENEMY;

// �t��̐���
void eFormation(
	float x, float y,  // �����n���̍��W
	int count          // �t����\������G��?
) {
	ENEMY* enemy;      // �G��\���\���̂ւ̃|�C?�^
	ENEMY* prec=NULL;  // 1�O�̓G���w���|�C?�^
	
	// �t����\������G�����F
	// �G�̍\���̂��m�����C���W��?��������B
	// �\���̊m���̋�̓I��??��NewEnemyType��?�ōs�ӂƂ���B
	for (int i=0; i<count; i++, prec=enemy) {
		enemy=NewEnemyType();
		enemy->X=x;
		enemy->Y=y;
		for (int j=0; j<INTERVAL; j++) {
			enemy->OldX[j]=x;
			enemy->OldY[j]=y;
		}
		enemy->Index=0;

		// ����ȊO�̓G��1�O�̓G���Q�Ƃ��C
		// ��[�̓G��NULL���Q�Ƃ���B
		enemy->Prec=prec;
	}
}

