void MoveAimingBulletFP(
	int& x, int& y,  // �e�̍��W
	int vx, int vy   // �e�̑��g
) {
	// �e�̍��W(x,y)�ɑ��g(vx,vy)�����V��
	x+=vx;
	y+=vy;

	// �e��`���F
	// ��ʂɒe��`���ƪ��ɂ͍��W��(x>>8, y>>8)�Ƃ���B
	// �e��`����̓I��??��Draw��?�ōs�ӂƂ���B
	Draw(x>>8, y>>8);
}