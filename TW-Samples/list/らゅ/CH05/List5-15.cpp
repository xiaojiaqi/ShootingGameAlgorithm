void SwitchColors(
	bool color_button,   // �F�؂�ַV�{�^?�̏���
	bool shot_button,    // �V?��g�{�^?�̏���
	int num_bullet,      // �e��?
	bool bullet_color[]  // �e�̐F
) {
	static bool prev_col_button=false;  // �O��̃{�^?�̏���
	static bool color=true;             // ���@�̐F
	static int energy=0;                // �G�l?�M�[
	
	// �F��؂�ַV��
	if (!prev_col_button && color_button) color=~color;
	prev_col_button=color_button;
	
	// �V?��g��?�F
	// ���@�Ɠ����F�̃V?��g��?�B
	// �V?��g�̋�̓I��??��Shot��?�ōs�ӂƂ���B
	if (shot_button) Shot(color);
	
	// �e�Ƃ�?���蔻�]??�F
	// ���]�̋�̓I��??��HitBullet��?�ōs�ӂƂ���B
	for (int i=0; i<num_bullet; i++) {
		if (HitBullet(i)) {
			
			// �����F�Ȃ�΋z���F
			// �e�������C�G�l?�M�[��?�₷�B
			// ��?�̋�̓I��??��DeleteBullet��?�ōs�ӂƂ���B
			if (color==bullet_color[i]) {
				DeleteBullet(i);
				energy++;
			}
			
			// �قȂ�F�Ȃ�΃~�X�F
			// �~�X�̋�̓I��??��Miss��?�ōs�ӂƂ���B
			else {
				Miss();
			}
		}
	}
}

