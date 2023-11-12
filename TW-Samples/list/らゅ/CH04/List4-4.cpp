void SemiAutoShot(
	bool button,    // �{�^?�̏��ԁi?���ꂽ�ƪ�true�j
	int min_power,  // ���߃p?�[�̍ŏ��l
	int max_power,  // ���߃p?�[�̍ő�l
	int max_gauge   // �A�˃Q�[�W�̍ő�l
) {
	// ���߃p?�[�C�A�˃Q�[�W
	static int power=0, gauge=0;

	// �{�^?��?���Ă����?
	if (button) {
		
		// ���߃p?�[�s���̏�?�F
		// �ʏ�̒e��?�B
		// ��̓I��??��Shot��?�ōs�ӂƂ���B
		if (power<min_power) Shot();
	
		// ���߃p?�[�ϕ��̏�?�F
		// ���ߏ��Ԃ̕\��������B
		// ��̓I��??��PowerEffect��?�ōs�ӂƂ���B
		else PowerEffect();
	
		// ���߃p?�[��?�₵�C�A�˃Q�[�W���ő�ɂ���
		if (power<max_power) power++;
		gauge=max_gauge;
	}
	
	// �{�^?�𗣂��Ă����?�F
	else {
		
		// ���߃p?�[�ϕ��̏�?�F
		// ����?���e��?�F
		// �ő�p?�[�̂ƪ��͓��ʂȒe��?�B
		// ��̓I��??��MaxShot��?��BigShot��?�ōs�ӂƂ���B
		if (min_power<=power) {
			if (power==max_power) MaxShot(); 
				else BigShot(power);
			gauge=0;
		}
		
		// �A�˃Q�[�W>0�̏�?�F
		// �ʏ�̒e��?���C�A�˃Q�[�W��-1����B
		// ��̓I��??��Shot��?�ōs�ӂƂ���B
		if (gauge>0) {
			Shot();
			gauge--;
		}

		// ���߃p?�[��0�ɂ���
		power=0;
	}
}
