// ���̏�����?����\����
typedef struct {
	int X, Y;    // ���W
	int VX, VY;  // ���g
	int Color;     // �F
} STAR;

// ���̃X�N?�[?
void DrawStar(
	int num_star,   // ����?
	STAR star[]    // ���̏��
) {
	// ���̈ړ��ƕ`��F
	// �`��̋�̓I��??��DrawPixel��?�ōs�ӂƂ���B
	for (int i=0; i<num_star; i++) {
		star[i].X+=star[i].VX;
		star[i].Y+=star[i].VY;
		DrawPixel(star[i].X, star[i].Y, star[i].Color);
	}
}

