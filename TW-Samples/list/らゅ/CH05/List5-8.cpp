// �[?�̏��ԁF
// �ҋ@�C�L�тĂ���r?�C�L�Ѫ������C�k��ł���r?�B
typedef enum {
	READY, EXTENDING, EXTENDED, SHRINKING
} STATE_TYPE;

// �[?�̓���
void MoveArm(
	bool button  // �[?��L�΂��{�^?�̏���
) {
	static STATE_TYPE state=READY;  // �[?�̏���
	static int length;              // �[?�̒���
	static int max_length=20;       // �[?�̍ő咷
	static int time;                // ?�ԑ҂��p
	
	// �[?�̏��Ԃɂ����??��ϷV��
	switch (state) {
		
		// �ҋ@�F
		// �{�^?�m?���ꂽ��[?��L�΂��B
		case READY:
			if (button) {
				state=EXTENDING;
				length=0;
			}
			break;
		
		// �L�тĂ���r?�F
		// �[?��L�΂��C
		// �ő咷�ɒB������L�Ѫ��������ԂɈڂ�B
		case EXTENDING:
			if (length<max_length) {
				length++;
			} else {
				state=EXTENDED;
				time=10;
			}
			break;
		
		// �L�Ѫ������F
		// ��]?�Ըm�o�߂�����k�܂���B
		case EXTENDED:
			if (time>0) {
				time--;
			} else {
				state=SHRINKING;
			}
			break;
		
		// �k��ł���r?�F
		// �����m0�ɂȂ�����ҋ@���Ԃɖ߂�B
		case SHRINKING:
			if (length>0) {
				length--;
			} else {
				state=READY;
			}
			break;
	}
}

