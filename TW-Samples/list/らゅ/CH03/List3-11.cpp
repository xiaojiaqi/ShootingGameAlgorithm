// ���@�̏��ԁi���s�C�㏸�C���~�j
typedef enum {
	WALKING, JUMP_UP, JUMP_DOWN
} MYSHIP_STATE;

// ���@�̓���
void Walk(
	float& x, float& y,     // ���@�̍��W
	float speed,            // ���@�̑���
	bool left, bool right,  // �X�e�B��N���́i�����j
	bool jump_button        // �W??�v�{�^?�̓���
) {
	static MYSHIP_STATE state=WALKING;  // ���@�̏���
	static int time;                    // �W??�v��?��
	
	// �����ւ̈ړ�
	if (left ) x-=speed;
	if (right) x+=speed;

	// ���Ԃɂ���ĕ��򂷂�
	switch (state) {

		// ���s�F
		// �W??�v�{�^?��?������㏸���ԂɈڍs����B
		case WALKING:
			if (jump_button) {
				state=JUMP_UP;
				time=40;
			}
			break;
		
		// �㏸�F
		// ��]?�ԏ㏸�����牺�~���ԂɈڍs����B
		case JUMP_UP:
			y-=speed;
			if (time==0) {
				state=JUMP_DOWN;
				time=40;
			} else time--;
			break;
		
		// ���~�F
		// ��]?�ԉ��~��������s���Ԃɖ߂�B
		case JUMP_DOWN:
			y+=speed;
			if (time==0) state=WALKING; else time--;
			break;
	}
}
