void Draw(int roll);

void RollMyShip3D(
	int& roll,             // ?�[?�̊p�g
	bool left, bool right  // �������؂ւ̃X�e�B��N����
) {
	// �X�e�B��N�ō�����͂�����?�F
	// -60<roll�Ȃ��roll��-3����B
	if (left && -60<roll) roll-=3;

	// �X�e�B��N�Ņ�����͂�����?�F
	// roll<60�Ȃ��roll��+3����B
	if (right && roll<60) roll+=3;

	// �X�e�B��N�ō����������͂��Ă��Ȃ���?�F
	// roll�m0�ɋ߂Â���ӂɂ���B
	if (!left && !right) {
		if (roll<0) roll+=3; else
		if (0<roll) roll-=3;
	}

	// roll�̒l��?���Ď��@����]�����ĕ\������F
	// �\���̋�̓I��??��Draw��?�ōs�ӂƂ���B
	Draw(roll);
}