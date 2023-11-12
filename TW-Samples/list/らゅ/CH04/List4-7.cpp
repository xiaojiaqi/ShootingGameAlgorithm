void LockShot(
	bool button,     // �{�^?�̏��ԁi?���ꂽ�ƪ�true�j
	int min_power,   // ���߃p?�[�̍ŏ��l
	int max_gauge,   // �A�˃Q�[�W�̍ő�l
	int enemy_id,    // ?��N�V?��g�m�ǔ����Ă���G��ID
	                 // �i�ǔ����Ă��Ȃ��ƪ��ɂ�?�̒l�j
	float front_dir  // ���@�̐��ʂ�??�������
) {
	// ���߃p?�[�C�A�˃Q�[�W
	static int power=0, gauge=0;

	// �{�^?��?���Ă����?
	if (button) {
		
		// ���߃p?�[�s���̏�?�F
		// ���߃p?�[��?�₵�C�A�˃Q�[�W���ő�ɂ��āC
		// �e��?�B��̓I��??��Shot��?�ōs�ӂƂ���B
		if (power<min_power) {
			power++;
			gauge=max_gauge;
			Shot();
		}
	
		// ���߃p?�[�ϕ��̏�?�F
		// �A�˃Q�[�W��0�ɂ��āC?��N�V?��g��?�B
		else {
			gauge=0;
			
			// ?��N�V?��g��?�F
			// �G��ǔ����Ă���ƪ��͓G��_��?������B
			// �i�u���@���؂����Ĕ�Ԓe�v�Ɠ��l�j
			// �G��ǔ����Ă��Ȃ��ƪ��͎��@�̐��ʂɒe��?�B
			// �i�u���R�ȕ��؂ɔ�Ԓe�v�Ɠ��l�j
			// ���ꂼ���̓I��??��AimingShot��?��
			// DirectedShot��?�ōs�ӂƂ���B
			if (enemy_id>=0) {
				AimingShot(enemy_id);
			} else {
				DirectedShot(front_dir);
			}
		}
	}
	
	// �{�^?�𗣂��Ă����?�F
	else {
		
		// �A�˃Q�[�W>0�̏�?�F
		// ?�ʂ̒e��?���C�A�˃Q�[�W��-1����B
		if (gauge>0) {
			Shot();
			gauge--;
		}

		// ���߃p?�[��0�ɂ���
		power=0;
	}
}
