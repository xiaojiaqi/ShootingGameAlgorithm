void MoveAimingBulletDDA(
	int& x, int& y,  // 弾の座標
	int vx, int vy,  // 弾の移動方ﾅﾘ
	int dx, int dy,  // X方ﾅﾘとY方ﾅﾘのﾋ�分
	int& diff,       // 誤ﾋ�
	int speed        // 弾の速さ
) {
	// 移動?離のX方ﾅﾘｸm長いとｪｽの??
	if (dx>=dy) {
		for (int i=0; i<speed; i++) {

			// X方ﾅﾘには?回移動させる
			x+=vx;
			
			// Y方ﾅﾘには誤ﾋ�ｸmｶﾔ積したとｪｽだけ移動させる
			diff+=dy;
			if (diff>=dx) {
				diff-=dx;
				y+=vy;
			}
		}
	} 

	// 移動?離のY方ﾅﾘｸm長いとｪｽの??
	else {
		for (int i=0; i<speed; i++) {

			// Y方ﾅﾘには?回移動させる
			y+=vy;

			// X方ﾅﾘには誤ﾋ�ｸmｶﾔ積したとｪｽだけ移動させる
			diff+=dx;
			if (diff>=dy) {
				diff-=dy;
				x+=vx;
			}
		}
	}
}
