// �{�X�̏��ԁF
// �U?0�C�U?1�C�U?2�C�ҋ@
typedef enum {
	ATTACK0, ATTACK1, ATTACK2, WAIT
} BOSS_STATE;


// �e���Ԃ̐���?��
int Time[]={30, 40, 25, 20};

// �{�X�̍s��
void MoveBoss(
	BOSS_STATE& state,  // ���݂̏���
	int& timer           // �^�C�}�[
) {
	// �U?�F
	// ���Ԃ�?�����U?���s�ӁB�ҋ@�̂ƪ��ɂ��e�����Ȃ��B
	// �U?�̋�̓I��??�́C
	// Attack0�CAttack1�CAttack2�̊e��?�ōs�ӂƂ���B
	switch (state) {
		case ATTACK0: Attack0(); break;
		case ATTACK1: Attack1(); break;
		case ATTACK2: Attack2(); break;
	}
	
	// ���ԑJ�ځF
	// �^�C�}�[�����Z���C
	// �e���Ԃ̐���?�Ԃ𒴷V����?�̏��ԂɈڍs����B
	timer++;
	if (timer>Time[state]) {
		state=(BOSS_STATE)((state+1)%4);
		timer=0;
	}
}

