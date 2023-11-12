// �G�̏��Ԃ�\���]?�F
// ?���i�o���O�j�C�o���C?���C����
typedef enum {
	READY, APPEAR, ACT, DISAPPEAR
} STATE_TYPE;

// �o���Ə����ɂ�����?�ԁC?��?��
#define TIME 30
#define ACT_TIME 180

// ��?�Ɍ����G��??
void EmergingEnemy(
	int num_enemy,           // �G��?
	STATE_TYPE state[],      // �G�̏���
	float ex[], float ey[],  // �G�̍��W
	float alpha[],           // ��?�t�͒l
	int timer[]              // �^�C�}�[
) {
	// �S�Ă̓G�Ɋւ���?�[�v
	for (int i=0; i<num_enemy; i++) {
		
		// ���Ԃ�?���ĕ���
		switch (state[i]) {
			
			// ?���i�o���O�j�F
			// ��?�t�͒l�ƃ^�C�}�[��?�������āC
			// �o�����ԂɈڍs����B
			case READY:
				state[i]=APPEAR;
				alpha[i]=0;
				timer[i]=TIME;
				break;
			
			// �o���F
			// ��?�t�͒l�����񂾂�媽������B
			// �^�C�}�[�m0�ɂȂ�����?�����ԂɈڍs����B
			case APPEAR:
				alpha[i]=(float)(TIME-timer[i])/TIME;
				timer[i]--;
				if (timer[i]==0) {
					state[i]=ACT;
					timer[i]=ACT_TIME;
				}
				break;
			
			// ?���F
			// �ړ���U?���s�ӁB
			// �^�C�}�[�m0�ɂȂ�����������ԂɈڍs����B
			// �ړ���U?�̋�̓I��??�́C
			// MoveEnemy��?�ōs�ӂƂ���B
			case ACT:
				MoveEnemy(i);
				timer[i]--;
				if (timer[i]==0) {
					state[i]=DISAPPEAR;
					timer[i]=TIME;
				}
				break;
			
			// �����F
			// ��?�t�͒l�����񂾂񏬂�������B
			// �^�C�}�[�m0�ɂȂ�����G�������B
			// �G��������̓I��??�́C
			// DeleteEnemy��?�ōs�ӂƂ���B
			case DISAPPEAR:
				alpha[i]=(float)timer[i]/TIME;
				timer[i]--;
				if (timer[i]==0) {
					DeleteEnemy(i);
				}
				break;
		}
		
		// �G�̕\���F
		// ��?�t�͒l�Ɋ�Â��ĥ�?�t��?���\�����s�ӁB
		DrawEnemy(ex[i], ey[i], alpha[i]);
	}
}
