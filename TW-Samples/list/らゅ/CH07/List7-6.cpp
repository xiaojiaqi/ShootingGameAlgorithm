#include <math.h>

void DrawChip(int id, int x, int y);

// �`��v?�iX���؁CY���؁j
#define XMAX 20
#define YMAX 400

// �w�ނ̕\��
void DrawBG(
	int sx, int sy,      // ��ʂ�?�S���W
	int sw, int sh,      // ��ʂ̑媽��
	int cw, int ch,      // �`��v�̑媽��
	int map[YMAX][XMAX]  // �w�ރf�[�^�i�`��v��?�̔z��j
) {
	// ��]�ŉ�ʅ��ɓ���w�ނ̍ő��ʤ��?�߂�
	int w2=sw/2, h2=sh/2;            // ��ʂ�?��?����1/2
	int r=(int)sqrt(w2*w2+h2*h2);    // �~�̔��a
	int x0=(sx-r)/cw, y0=(sy-r)/ch;  // ����[�̃`��v
	int x1=(sx+r)/cw, y1=(sy+r)/ch;  // �����[�̃`��v

	// �`��v�̕`��F
	// �e�`��v�̕`���DrawChip��?�ōs�ӂƂ���B
	for (int i=y0; i<=y1; i++) {
		for (int j=x0; j<=x1; j++) {
			DrawChip(map[i][j], j*cw-sx+sw/2, i*ch-sy+sh/2);
		}
	}
}

