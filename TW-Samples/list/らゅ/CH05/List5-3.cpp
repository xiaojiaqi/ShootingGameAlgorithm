void InducedExplosion(
	float ex0[], float ey0[],  // �G�̍�����W
	float ex1[], float ey1[],  // �G�̅������W
	int num_enemy,             // �G��?
	float x0[], float y0[],    // ??�̍�����W
	float x1[], float y1[],    // ??�̅������W
	int num_explosion          // ??��?
) {
	// �G��??��?���蔻�]??�F
	// �S�Ă̓G��??�Ƃ̊Ԃ�?���蔻�]??���s���C
	// �G�m??��?��������j�󂷂�B
	// �����ēG�Ɠ������W���肽��??�𐶐�����B
	// �j��Ɛ����̋�̓I��??�́C
	// DestroyEnemy�CCreateExplosion�̊e��?�ōs�ӂƂ���B
	for (int i=0; i<num_enemy; i++) {
		for (int j=0; j<num_explosion; j++) {
			if (ex0[i]<x1[j] && x0[j]<ex1[i] && 
				ey0[i]<y1[j] && y0[j]<ey1[i]) {
				DestroyEnemy(i);
				CreateExplosion(ex0[i], ey0[i]);
			}
		}
	}
}
