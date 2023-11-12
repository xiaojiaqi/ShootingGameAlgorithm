void CapturedEnemy(
	float& x0, float& y0,      // �����ɂȂ����G�̍�����W
	float& x1, float& y1,      // �����ɂȂ����G�̅������W
	float ex0[], float ey0[],  // ���̓G�̍�����W
	float ex1[], float ey1[],  // ���̓G�̅������W
	int num_enemy,             // ���̓G��?
	float bx0[], float by0[],  // �e�̍�����W
	float bx1[], float by1[],  // �e�̅������W
	int num_bullet,            // �e��?
	bool button                // �V?��g�{�^?�̏���
) {
	static int damage;         // ���݂̃_?�[�W
	static int max_damage=40;  // �_?�[�W�̌��E�l

	// �G�Ƃ�?���蔻�]??�F
	// �G�Əժw������C�G�Ƀ_?�[�W��^�V�C
	// �������_?�[�W���󂯂�B
	// �_?�[�W�t�^�̋�̓I��??�́C
	// DamageEnemy��?�ōs�ӂƂ���B
	for (int i=0; i<num_enemy; i++) {
		if (ex0[i]<x1 && x0<ex1[i] && 
			ey0[i]<y1 && y0<ey1[i]) {
			DamageEnemy(i);
			damage++;
		}
	}
	
	// �e�Ƃ�?���蔻�]??�F
	// �e�Əժw������C�e�������C
	// �������_?�[�W���󂯂�B
	// ��?�̋�̓I��??�́C
	// DeleteBullet��?�ōs�ӂƂ���B
	for (int i=0; i<num_bullet; i++) {
		if (bx0[i]<x1 && x0<bx1[i] && 
			by0[i]<y1 && y0<by1[i]) {
			DeleteBullet(i);
			damage++;
		}
	}
	
	// ?���?�F
	// ���@�̃V?��g?���?�킹�ăV?��g��?�B
	// ���˂̋�̓I��??��Shot��?�ōs�ӂƂ���B
	if (button) Shot();

	// �_?�[�W���]�F
	// �_?�[�W�m���E�l�܂ŶԐς�������ł���B
	// ���ł̋�̓I��??�́C
	// DeleteCapturedEnemy��?�ōs�ӂƂ���B
	if (damage>=max_damage) DeleteCapturedEnemy();
}
