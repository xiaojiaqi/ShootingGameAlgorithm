void DeleteShot();

void MoveShot(
	float& x0, float& y0,  // �V?��g�̍�����W
	float& x1, float& y1,  // �V?��g�̅������W
	float vx, float vy,    // �V?��g�̑��g�iX���؁CY���؁j
	float sx0, float sy0,  // ��ʘg�̍�����W
	float sx1, float sy1   // ��ʘg�̅������W
) {
	// �V?��g�m��ʊO�ɏo�Ă���������F
	// ��̓I��??��DeleteShot��?�ōs�ӂƂ���B
	if (x1<=sx0 || sx1<=x0 || y1<=sy0 || sy1<=y0) DeleteShot();

	// �V?��g���ړ�����i���W���X�肷��j
	x0+=vx; y0+=vy;
	x1+=vx; y1+=vy;
}