void ScrollForce(
	int& x, int& y,   // ���@�̍��W
	int vx, int vy,   // ���@�̑��g
	int svx, int svy  // �X�N?�[?�̑��g
) {
	x+=vx+svx/2;
	y+=vy+svy/2;
}