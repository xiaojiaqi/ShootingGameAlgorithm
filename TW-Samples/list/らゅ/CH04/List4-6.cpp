void ShotAndLaser(
	bool button,    // �{�^?�̏��ԁi?���ꂽ�ƪ�true�j
	int min_power,  // ���߃p?�[�̍ŏ��l
	int max_gauge   // �A�˃Q�[�W�̍ő�l
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
		// �A�˃Q�[�W��0�ɂ��āC?�[�U�[��?�B
		// ��̓I��??��Laser��?�ōs�ӂƂ���B
		else {
			gauge=0;
			Laser();
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
