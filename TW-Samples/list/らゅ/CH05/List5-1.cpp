void Bomb(
	int& bomb_time,             // �{?�̗L��?��
	float x0, float y0,        // �{?�̗L����ʤ�̍�����W
	float x1, float y1,        // �{?�̗L����ʤ�̅������W
	float bx0[], float by0[],  // �e�̍�����W
	float bx1[], float by1[],  // �e�̅������W
	int num_bullet,            // �e��?
	float ex0[], float ey0[],  // �G�̍�����W
	float ex1[], float ey1[],  // �G�̅������W
	int num_enemy              // �G��?
) {
	// �{?�m�L���ȏ�?��??
	if (bomb_time>0) {
	
		// �e�������F
		// ��?�̋�̓I��??�́C
		// DeleteBullet��?�ōs�ӂƂ���B
		for (int i=0; i<num_bullet; i++) {
			if (bx0[i]<x1 && x0<bx1[i] && 
				by0[i]<y1 && y0<by1[i]) {
				DeleteBullet(i);
			}
		}

		// �G�Ƀ_?�[�W��^�V��F
		// �_?�[�W�t�^�̋�̓I��??�́C
		// DamageEnemy��?�ōs�ӂƂ���B
		for (int i=0; i<num_enemy; i++) {
			if (ex0[i]<x1 && x0<ex1[i] && 
				ey0[i]<y1 && y0<ey1[i]) {
				DamageEnemy(i);
			}
		}
	
		// �{?�̗L��?�Ԃ����炷
		bomb_time--;
	}
}

