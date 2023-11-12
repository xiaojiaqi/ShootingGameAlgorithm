// �`��v?�iX���؁CY���؁j
#define XMAX 1000
#define YMAX 50

// �㉺�����m�ȸm�����w�ނ̕\��
void DrawCirculatedBG(
	int sx, int sy,      // ��ʍ���ɤI?����w�ޏ�̈ʒu
	int sw, int sh,      // ��ʂ̑媽��
	int cw, int ch,      // �`��v�̑媽��
	int map[XMAX][YMAX]  // �w�ރf�[�^�i�`��v��?�̔z��j
) {
	// �`�悷��`��v�̔�ʤ
	int x0=sx/cw, y0=sy/ch;    // ����[�̃`��v
	int x1=(sx+sw-1)/cw%XMAX, 
		y1=(sy+sh-1)/ch%YMAX;  // �����[�̃`��v

	// �`��v�̕`��F
	// �e�`��v�̕`���DrawChip��?�ōs�ӂƂ���B
	for (int i=x0; i!=x1+1; i=(i+1)%XMAX) {
		for (int j=y0; j!=y1+1; j=(j+1)%YMAX) {
			DrawChip(map[i][j], j*cw-sx, i*ch-sy);
		}
	}
}
