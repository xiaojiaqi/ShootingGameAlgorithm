void OverlaidScroll(
	int num_bg,           // �w�ނ�?
	int sx[], int sy[],   // �e�w�ޏ�̕\���ʒu
	int svx[], int svy[]  // �e�w�ނ̃X�N?�[?���g
) {
	// �S�w�ނ̕`��F
	// �e�w�ނ̕\���ʒu��?�ɍX�肵����ɕ\������B
	// �\���̋�̓I��??��DrawBG��?�ōs�ӂƂ���B
	for (int i=0; i<num_bg; i++) {
		sx[i]+=svx[i];
		sy[i]+=svy[i];
		DrawBG(i);
	}
}
