void MoveReflectShot(
	float& x0, float& y0,      // �V?��g�̍�����W
	float& x1, float& y1,      // �V?��g�̅������W
	float& vx, float& vy,      // �V?��g�̑��g�i?���C?���j
	float gx0[], float gy0[],  // �n�`�̍�����W
	float gx1[], float gy1[],  // �n�`�̅������W
	int num_ground,            // �n�`��?
	float ex0[], float ey0[],  // �G�̍�����W
	float ex1[], float ey1[],  // �G�̅������W
	int num_enemy              // �G��?
) {
	// �n�`�Ƃ�?���蔻�]??�F
	// �V?��g��?�����؂ɐi�߂����W�ɂ��āC
	// �n�`��?���邩�Ǵӂ��𔻃]����B
	// �n�`��?��������?�ɂ́C?�����؂̑��g����ɂ��āC
	// ?�[�v���甲����B
	for (int i=0; i<num_ground; i++) {
		if (gx0[i]<x1 && x0<gx1[i] && 
			gy0[i]<y1+vy && y0+vy<gy1[i]) {
			vy=-vy;
			break;
		}
	}
	
	// �V?��g��i�߂�
	x0+=vx; y0+=vy;
	x1+=vx; y1+=vy;

	// �G�Ƃ�?���蔻�]??�F
	// �G��?��������?�ɂ́C�G�Ƀ_?�[�W��^�V�āC
	// ?�[�v���甲����B
	// �_?�[�W�̋�̓I��??��DamageEnemy��?�ōs�ӂƂ���B
	for (int i=0; i<num_enemy; i++) {
		if (ex0[i]<x1 && x0<ex1[i] && 
			ey0[i]<y1 && y0<ey1[i]) {
			DamageEnemy(i);
			break;
		}
	}
}
