void Draw(int x, int y);

void InitAimingBulletFP(
	int mx, int my,    // ���@�̍��W
	int ex, int ey,    // �G�̍��W
	int& x, int& y,    // �e�̍��W
	int& vx, int& vy,  // �e�̑��g
	int speed          // �e�̑���
) {
	// �e�̍��W��݃]����
	x=ex; y=ey;

	// �ڕW�ɤI����X���؂�Y���؂������̐�I�l(dx,dy)��?�߂�
	int dx=mx>=ex?mx-ex:ex-mx;
	int dy=my>=ey?my-ey:ey-my;

	// X���؂�Y���؂������̴ӂ���������?��d�Ƃ���
	int d=dx>=dy?dx:dy;

	// ���g(vx,vy)��?�߂�
	vx=(mx-ex)*speed/d;
	vy=(my-ey)*speed/d;
}