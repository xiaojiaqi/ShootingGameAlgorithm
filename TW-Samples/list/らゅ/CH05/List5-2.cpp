// �ߐڍU?�Ɋւ���??
void Punch(
	bool button,               // �{�^?�̏��ԁi?�����ƪ�true�j
	float px0, float py0,      // �ߐڍU?�̍�����W
	float px1, float py1,      // �ߐڍU?�̅������W
	float ex0[], float ey0[],  // �G�̍�����W
	float ex1[], float ey1[],  // �G�̅������W
	int num_enemy              // �G��?
) {
	static bool punching=false;  // �ߐڍU??���Ǵӂ�
	static int punch_time;       // �ߐڍU?���o���Ă���?��
	
	// �ߐڍU?�̊J�n�F
	// �ߐڍU??�ł͂Ȃ��C�{�^?�m?����Ă�����C
	// �ߐڍU?���o���B
	if (!punching && button) {
		punching=true;
		punch_time=30;
	}
	
	// �ߐڍU??��??
	if (punching) {

		// �G�Ƃ�?���蔻�]??�F
		// �_?�[�W��^�V���̓I��??�́C
		// DamageEnemy��?�ōs�ӂƂ���B
		for (int i=0; i<num_enemy; i++) {
			if (ex0[i]<px1 && px0<ex1[i] && 
				ey0[i]<py1 && py0<ey1[i]) {
				DamageEnemy(i);
			}
		}

		// �ߐڍU?�̕\���F
		// �\���̋�̓I��??��DrawPunch��?�ōs�ӂƂ���B
		DrawPunch();

		// �ߐڍU?��?���ƏI���F
		// ?��?�Ԃ����\����ߐڍU?������?�߂�B
		if (punch_time==0) punching=false; else punch_time--;
	}
}
