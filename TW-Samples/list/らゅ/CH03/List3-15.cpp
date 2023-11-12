// �p?�[�ª�v�̎��
typedef enum {
	NONE,  // ���[�\?�m�Ȃ�����
	SPEED, MISSILE, DOUBLE, 
	LASER, OPTION, BARRIER, 
	END    // �Q�[�W�̅��[������
} POWER_UP_TYPE;

// �Q�[�W���g�����p?�[�ª�v
void PowerUpGauge(
	bool power_up_button  // �p?�[�ª�v�{�^?�̓���
) {
	static POWER_UP_TYPE cursor=NONE;  // ���[�\?�̈ʒu
	
	// �C�e?���E�����ƪ���??�F
	// �C�e?���E������C���[�\?��1���ɓ������B
	// ���[�܂œ������獶�[�ɖ߂��B
	// �E�����]??��PickItem��?�ōs�ӂƂ���B
	if (PickItem()) {
		cursor++;
		if (cursor==END) cursor=SPEED;
	}
	
	// �p?�[�ª�v��??�F
	// �{�^?�m?���ꂽ��C
	// ���[�\?�m�w���Ă���p?�[�ª�v���s�ӁB
	// ��̓I��??��PowerUp��?�ōs�ӂƂ���B
	if (power_up_button) {
		PowerUp(cursor);
	}
}

