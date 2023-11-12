void MoveThrownEnemy(
	float& x0, float& y0,      // ?�Ƃ���ꂽ�G�̍�����W
	float& x1, float& y1,      // ?�Ƃ���ꂽ�G�̅������W
	float vx, float vy,        // ?�Ƃ���ꂽ�G�̑��g
	float ex0[], float ey0[],  // ���̓G�̍�����W
	float ex1[], float ey1[],  // ���̓G�̅������W
	int num_enemy              // ���̓G��?
) {
	// �G�Ƃ�?���蔻�]??�F
	// ?�Ƃ���ꂽ�G�ƁC���̑S�Ă̓G�Ƃ̊Ԃ�
	// ?���蔻�]??���s�ӁB
	// �ժw������C?�Ƃ���ꂽ�G�������C
	// �����??���o���B
	// ���łƏo���̋�̓I��??�́C
	// DeleteEnemy�CCreateExplosion�̊e��?�ōs�ӂƂ���B
	int i;
	for (i=0; i<num_enemy; i++) {
		if (ex0[i]<x1 && x0<ex1[i] && 
			ey0[i]<y1 && y0<ey1[i]) {
			DeleteEnemy(i);
			CreateExplosion(x0, y0);
		}
	}
	
	// �ǂ̓G�ɂ��Ԃ���Ȃ�������?�F
	// ?�Ƃ���ꂽ�G�𓮂����B
	if (i==num_enemy) {
		x0+=vx; y0+=vy;
		x1+=vx; y1+=vy;
	}
}


