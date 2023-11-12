// �G�̏��ԁF
// �ʏ�C�ߑ�
typedef enum {
	NORMAL, CAPTURED
} CAPTOR_STATE;

// ���@���Ƃ�V��G�̓���
void Captor(
	bool capture  // ����C�ߑ��U?�����邩�Ǵӂ�
) {
	static int state=NORMAL;  // �G�̏���
	
	// ���Ԃɂ���ĕ��򂷂�
	switch (state) {
		
		// �ʏ���ԁF
		// �ʏ�U?�܂��͕ߑ��U?���s�ӁB
		// �ߑ��U?�m����������ߑ����ԂɈڂ�B
		// �U?�̋�̓I��??�́CCaptureAttack�C
		// NormalAttack�̊e��?�ōs�ӂƂ���B
		case NORMAL:
			if (capture) {
				if (CaptureAttack()) state=CAPTURED;
			} else {
				NormalAttack();
			}
			break;
		
		// �ߑ����ԁF
		// �ʏ�U?���s�ӁB
		// �j�󂳂ꂽ�玩�@��Ԃ�����ɏ��ł���B
		// ���]�Ȃǂ̋�̓I��??�́CDestroyed�C
		// ReturnMyShip�CDelete�̊e��?�ōs�ӂƂ���B
		case CAPTURED:
			NormalAttack();
			if (Destroyed()) {
				ReturnMyShip();
				Delete();
			}
			break;
	}
}

