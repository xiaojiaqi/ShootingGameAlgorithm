void MoveAimingBulletDDA(
	int& x, int& y,  // �e�̍��W
	int vx, int vy,  // �e�̈ړ�����
	int dx, int dy,  // X���؂�Y���؂�����
	int& diff,       // ����
	int speed        // �e�̑���
) {
	// �ړ�?����X���ظm�����ƪ���??
	if (dx>=dy) {
		for (int i=0; i<speed; i++) {

			// X���؂ɂ�?��ړ�������
			x+=vx;
			
			// Y���؂ɂ͌����m�Ԑς����ƪ������ړ�������
			diff+=dy;
			if (diff>=dx) {
				diff-=dx;
				y+=vy;
			}
		}
	} 

	// �ړ�?����Y���ظm�����ƪ���??
	else {
		for (int i=0; i<speed; i++) {

			// Y���؂ɂ�?��ړ�������
			y+=vy;

			// X���؂ɂ͌����m�Ԑς����ƪ������ړ�������
			diff+=dx;
			if (diff>=dy) {
				diff-=dy;
				x+=vx;
			}
		}
	}
}
