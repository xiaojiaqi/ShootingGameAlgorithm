void Barrier1(
	float x0, float y0,        // �o?��?���蔻�]
	float x1, float y1,        // �i������W�C�������W�j
	float bx0[], float by0[],  // �e��?���蔻�]
	float bx1[], float by1[],  // �i������W�C�������W�j
	int num_bullet,            // �e��?
	float ex0[], float ey0[],  // �G��?���蔻�]
	float ex1[], float ey1[],  // �i������W�C�������W�j
	int num_enemy,             // �G��?
	int& damage,               // �o?�ɶԐς��ꂽ�_?�[�W
	int max_damage             // �o?�̃_?�[�W�̌��E�l
) {
	// �o?�ƒe�Ƃ�?���蔻�]??�F
	// �e�m?��������C�e�������C�o?�̃_?�[�W��?�₷�B
	// �e��������̓I��??��DeleteBullet��?�ōs�ӂƂ���B
	for (int i=0; i<num_bullet && damage<max_damage; i++) {
		if (bx0[i]<x1 && x0<bx1[i] && 
			by0[i]<y1 && y0<by1[i]) {
			DeleteBullet(i);
			damage++;
		}
	}

	// �o?�ƓG�Ƃ�?���蔻�]??�F
	// �G�m?��������C�G�Ƀ_?�[�W��^�V�C
	// �o?�̃_?�[�W��?�₷�B
	// �G�Ƀ_?�[�W��^�V���̓I��??�́C
	// DamageEnemy��?�ōs�ӂƂ���B
	for (int i=0; i<num_enemy && damage<max_damage; i++) {
		if (ex0[i]<x1 && x0<ex1[i] && 
			ey0[i]<y1 && y0<ey1[i]) {
			DamageEnemy(i);
			damage++;
		}
	}
	
	// �_?�[�W�m���E�l�𒴷V���ƪ��F
	// �o?�����ł�����B
	// ���ł̋�̓I��??��DeleteBarrier��?�ōs�ӂƂ���B
	if (damage>=max_damage) DeleteBarrier();
}
