// ���@�̏��ԁi�ʏ�C�o�[�T�[�N�C�ア�j
typedef enum {
	NORMAL, BERSERK, WEAK
} STATE_TYPE;

// �o�[�T�[�N���Ԃ�??
void Berserk(
	int num_shot,   // �����̃V?��g��?
	int num_enemy,  // �G��?
	int num_bullet  // �e�i�G�e�j��?
) {
	static STATE_TYPE state=NORMAL;  // ���@�̏��ԁi��?�͒ʏ�j
	static int energy=0;             // �G�l?�M�[
	static int berserk_energy=100;   // �o�[�T�[�N���Ԃ̔�����
	                                 // �җv�ȃG�l?�M�[
	static int time;                 // ���ʂ̎c��?��
	
	// ���Ԃ�?���ĕ��򂷂�
	switch (state) {
		
		// �ʏ����
		case NORMAL:

			// �ʏ�U?�F
			// ��̓I��??��NormalAttack��?�ōs�ӂƂ���B
			NormalAttack();

			// �G��e�Ƃ�?���蔻�]??�F
			// ?����ƃ~�X�ɂȂ�B
			// ���]��?�ʂ̋�̓I��??��HitEnemy�C
			// HitBullet�CMiss�̊e��?�ōs�ӂƂ���B
			for (int i=0; i<num_enemy; i++)
				if (HitEnemy(i)) Miss();
			for (int i=0; i<num_bullet; i++)
				if (HitBullet(i)) Miss();

			// �����̃V?��g�Ƃ�?���蔻�]??�F
			// �G�l?�M�[�𗭂߂�B
			// ���]��?�ʂ̋�̓I��??��HitShot�C
			// DeleteShot�̊e��?�ōs�ӂƂ���B
			for (int i=0; i<num_shot; i++) {
				if (HitShot(i)) {
					energy++;
					DeleteShot(i);
				}
			}

			// �G�l?�M�[�ʂ̔��]�F
			// �G�l?�M�[�m�ϕ��ɗ��܂�����
			// �o�[�T�[�N���ԂɈڍs����B
			// �G�l?�M�[�͎��R�Ɍ����Ă����B
			if (energy>=berserk_energy) {
				state=BERSERK;
				time=300;
			} else {
				energy--;
			}

			break;
		
		// �o�[�T�[�N����
		case BERSERK:

			// ����U?�F
			// ��̓I��??��SpecialAttack��?�ōs�ӂƂ���B
			SpecialAttack();

			// �G��e�Ƃ�?���蔻�]??�F
			// �G�Ƀ_?�[�W��^�V�C�e�͏����B
			// ?�ʂ̋�̓I��??��DamageEnemy�C
			// DeleteBullet�̊e��?�ōs�ӂƂ���B
			for (int i=0; i<num_enemy; i++)
				if (HitEnemy(i)) DamageEnemy(i);
			for (int i=0; i<num_bullet; i++)
				if (HitBullet(i)) DeleteBullet(i);
			
			// �c��?�Ըm�؂ꂽ��ア���ԂɈڍs����
			time--;
			if (time<=0) {
				state=WEAK;
				time=200;
			}
			
			break;
			
		// �ア����
		case WEAK:
			
			// �G��e�Ƃ�?���蔻�]??�F
			// ?����ƃ~�X�ɂȂ�B
			for (int i=0; i<num_enemy; i++)
				if (HitEnemy(i)) Miss();
			for (int i=0; i<num_bullet; i++)
				if (HitBullet(i)) Miss();

			// �c��?�Ըm�؂ꂽ��ʏ���ԂɈڍs����
			time--;
			if (time<=0) {
				state=NORMAL;
				energy=0;
			}
			
			break;
	}
}
