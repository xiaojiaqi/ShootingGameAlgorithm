void MoveDroppingBullet(
	float& x, float& y,   // �e�̍��W
	float accel,          // �����g
	float& vx, float& vy  // ���g��X������Y����
) {
	// ���g���X�肷��F
	// X�����͕ω��������CY����������ω�������B
	vy+=accel;

	// ���W���X�肷��
	x+=vx; y+=vy;
}