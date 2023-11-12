void Barrier2(
	float x0, float y0,        // �o?��?���蔻�]
	float x1, float y1,        // �i������W�C�������W�j
	float bx0[], float by0[],  // �e��?���蔻�]
	float bx1[], float by1[],  // �i������W�C�������W�j
	int num_bullet,            // �e��?
	float ex0[], float ey0[],  // �G��?���蔻�]
	float ex1[], float ey1[],  // �i������W�C�������W�j
	int num_enemy,             // �G��?
	int& energy,               // �o?�̃G�l?�M�[
	bool barrier_button        // �o?�{�^?�̏���
) {
	// �o?�𒣂�F
	// �o?�{�^?�m?����įu��C
	// ���G�l?�M�[�m?��ƪ��ɂ́C�o?�𒣂�B
	if (barrier_button && energy>0) {
	
		// �o?�ƒe�Ƃ�?���蔻�]??�F
		// �e�m?��������C�e�������C�o?�̃G�l?�M�[�����炷�B
		// �e��������̓I��??��DeleteBullet��?�ōs�ӂƂ���B
		for (int i=0; i<num_bullet && energy>0; i++) {
			if (bx0[i]<x1 && x0<bx1[i] && 
				by0[i]<y1 && y0<by1[i]) {
				DeleteBullet(i);
				energy--;
			}
		}

		// �o?�ƓG�Ƃ�?���蔻�]??�F
		// �G�m?��������C�G�Ƀ_?�[�W��^�V�C
		// �o?�̃G�l?�M�[�����炷�B
		// �G�Ƀ_?�[�W��^�V���̓I��??�́C
		// DamageEnemy��?�ōs�ӂƂ���B
		for (int i=0; i<num_enemy && energy>0; i++) {
			if (ex0[i]<x1 && x0<ex1[i] && 
				ey0[i]<y1 && y0<ey1[i]) {
				DamageEnemy(i);
				energy--;
			}
		}

		// �G�l?�M�[�̏���
		energy--;
	}
}


