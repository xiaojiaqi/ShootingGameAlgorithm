void MoveAcceleratedBullet(
	float speed,          // �e�̑���
	float accel,          // �����g
	float& vx, float& vy  // ���g��X������Y����
) {
	// ���g���Â�������?��
	if (speed!=0) {
		vx/=speed; vy/=speed;
	}

	// �������X�肷��
	speed+=accel;

	// ���g���肵���������|����
	vx*=speed; vy*=speed;
}