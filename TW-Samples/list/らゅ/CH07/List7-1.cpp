// �`��v?�iX���؁CY���؁j
#define XMAX 20
#define YMAX 400

// �w�ނ̕\��
void DrawBG(
	int sx, int sy,      // ��ʍ���ɤI?����w�ޏ�̈ʒu
	int sw, int sh,      // ��ʂ̑媽��
	int cw, int ch,      // �`��v�̑媽��
	int map[YMAX][XMAX]  // �w�ރf�[�^�i�`��v��?�̔z��j
) {
	// �`�悷��`��v�̔�ʤ
	int x0=sx/cw, y0=sy/ch;                // ����[�̃`��v
	int x1=(sx+sw-1)/cw, y1=(sy+sh-1)/ch;  // �����[�̃`��v

	// �`��v�̕`��F
	// �e�`��v�̕`���DrawChip��?�ōs�ӂƂ���B
	for (int i=y0; i<=y1; i++) {
		for (int j=x0; j<=x1; j++) {
			DrawChip(map[i][j], j*cw-sx, i*ch-sy);
		}
	}
}

