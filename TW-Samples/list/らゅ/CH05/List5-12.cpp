void ReinforcedShot(
	float x0, float y0,    // ���@�̍�����W
	float x1, float y1,    // ���@�̅������W
	float cx0, float cy0,  // �����@�̍�����W
	float cx1, float cy1,  // �����@�̅������W
	bool button            // �V?��g�{�^?�̏���
) {
	// �����Ɛڋ߂��Ă��邩�Ǵӂ��̔��]�F
	// �ڋ߂��Ă����?�ɂ͂p���V?��g�C
	// ���Ă��Ȃ���?�ɂ͒ʏ�̃V?��g��?�B
	// �V?��g��?��̓I��??�́C
	// SpecialShot�CNormalShot�̊e��?�ōs�ӂƂ���B
	if (button) {
		if (cx0<x1 && x0<cx1 && cy0<y1 && y0<cy1) {
			SpecialShot();
		} else {
			NormalShot();
		}
	}
}

