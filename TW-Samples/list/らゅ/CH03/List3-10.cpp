// �����̏��ԁi�ߑ��C?�V�C?�́j
typedef enum {
	CAPTURED, FLOATING, DOCKED
} DOCKING_STATE;

// ?�̂Ɋւ���??
void Docking(
	float& cx, float& cy,  // �����̍��W
	float ex, float ey,    // �G�̍��W
	float mx, float my,    // ���@�̍��W
	DOCKING_STATE& state   // �����̏���
) {
	// �����̏��Ԃɂ���ĕ��򂷂�
	switch (state) {
		
		// �ߑ��F
		// �G�ƈ�?�ɓ����B
		// �G�m�j�󂳂ꂽ��?�V���ԂɈڍs����B
		// �G�̔j�󔻃]??��EnemyDestroyed��?�ōs�ӂƂ���B
		case CAPTURED:
			cx=ex; cy=ey;
			if (EnemyDestroyed()) state=FLOATING;
			break;
		
		// ?�V�F
		// ���R�ɓ����B
		// �����ł͉�ʉ����؂ɒ��i����Ƃ���B
		// ���@�ɐڐG������?�̏��ԂɈڍs����B
		// �ڐG���]??��Catched��?�ōs�ӂƂ���B
		case FLOATING:
			cy++;
			if (Catched()) state=DOCKED;
			break;
		
		// ?�́F
		// ���@�ƈ�?�ɓ����B
		case DOCKED:
			cx=mx; cy=my;
			break;
	}
}
