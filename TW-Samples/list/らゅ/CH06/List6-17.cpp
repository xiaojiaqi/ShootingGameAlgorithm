#include <stdlib.h>

void Revenge(
	float rate,          // ?���Ԃ��̊m��
	float ex, float ey,  // �G�̍��W
	float tx, float ty   // �ڕW�i���@�j�̍��W
) {
	// �G�m�j�󂳂ꂽ���Ǵӂ��̔��]�F
	// ��̓I��??��Detroyed��?�ōs�ӂƂ���B
	if (Destroyed()) {
	
		// ?���Ԃ��F
		// ??���g���Ĉ�]�m����?���Ԃ��B
		// ?���Ԃ��e�́u�_��?���e�v�Ɠ����B
		// ���˂̋�̓I��??��AimingBullet��?�ōs�ӂƂ���B
		if (rand()<=rate*RAND_MAX) {
			AimingBullet(ex, ey, tx, ty);
		}
		
		// �G�������F
		// ��̓I��??��Delete��?�ōs�ӂƂ���B
		Delete();
	}
}
