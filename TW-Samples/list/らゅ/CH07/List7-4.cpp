void MixedScroll(
	int x, int y,  // ���@�̔w�ޏ�̍��W
	int w,         // ���@��?
	int sy,        // �X�N?�[?�ʒu��Y���W
	int svy,       // Y���؂̃X�N?�[?���g
	int sw,        // ���?
	int bw         // �w�ނ�?
) {
	// �w�ނ̕`��F
	// �X�N?�[?�ʒu���X�肵�C�w�ނ�`�悷��B
	// �`��̋�̓I��??��DrawBG��?�ōs�ӂƂ���B
	int sx=(bw-sw)*x/(bw-w);
	sy+=svy;
	DrawBG(sx, sy);
	
	// ���@�̕`��F
	// �X�N?�[?�ʒu�����?�I�ʒu�ɕ\������B
	// �`��̋�̓I��??��DrawMyShip��?�ōs�ӂƂ���B
	DrawMyShip(x-sx, y-sy);
}

