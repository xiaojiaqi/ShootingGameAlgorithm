void MoveAimingBullet(
	float& x, float& y,  // �e�̍��W
	float vx, float vy   // �e�̑��g
) {
	// �e�̍��W(x,y)�ɑ��g(vx,vy)�����V��
	x+=vx;
	y+=vy;
}