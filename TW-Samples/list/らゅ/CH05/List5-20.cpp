// ���ԁi�ʏ�C��?�C�U?�j
typedef enum {
	NORMAL, SIGHT, ATTACK
} STATE_TYPE;

// ���@�Ə�?�𓮂���
void MoveSight1(
	float& x, float& y,     // ���@�̍��W
	float& sx, float& sy,   // ��?�̍��W
	float speed,            // ���@�̈ړ��̑���
	float sight_speed,      // ��?�̈ړ��̑���
	bool up, bool down,     // �X�e�B��N���́i�㉺�j
	bool left, bool right,  // �X�e�B��N���́i�����j
	bool button             // ��?�{�^?����
) {
	static int state=NORMAL;  // ���ԁi�ʏ킩��J�n�j
	static int time;          // �U??��
	
	// ���Ԃ�?���ĕ��򂷂�
	switch (state) {
	
		// �ʏ���ԁF
		// ���@���ړ����C
		// �{�^?�m?���ꂽ���?���o���āC��?���ԂɈڂ�B
		case NORMAL:
			if (up   ) y-=speed;
			if (down ) y+=speed;
			if (left ) x-=speed;
			if (right) x+=speed;
			if (button) {
				state=SIGHT;
				sx=x; sy=y;
			}
			break;
		
		// ��?���ԁF
		// ��?���ړ����C�{�^?�m�����ꂽ��U?���ԂɈڂ�B
		case SIGHT:
			if (up   ) sy-=sight_speed;
			if (down ) sy+=sight_speed;
			if (left ) sx-=sight_speed;
			if (right) sx+=sight_speed;
			if (!button) {
				state=ATTACK;
				time=100;
			}
			break;
		
		// �U?���ԁF
		// ���@���ړ����C��]?�Ըm�o������ʏ���Ԃɖ߂�B
		case ATTACK:
			if (up   ) y-=speed;
			if (down ) y+=speed;
			if (left ) x-=speed;
			if (right) x+=speed;
			if (time==0) state=NORMAL;
			time--;
			break;
	}
}

