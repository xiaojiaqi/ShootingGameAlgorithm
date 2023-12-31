void Draw(int x, int y);

void InitAimingBulletFP(
	int mx, int my,    // 自機の座標
	int ex, int ey,    // 敵の座標
	int& x, int& y,    // 弾の座標
	int& vx, int& vy,  // 弾の速ﾃg
	int speed          // 弾の速さ
) {
	// 弾の座標を設ゾする
	x=ex; y=ey;

	// 目標に､IするX方ﾅﾘとY方ﾅﾘのﾋ�分の絶､I値(dx,dy)を?める
	int dx=mx>=ex?mx-ex:ex-mx;
	int dy=my>=ey?my-ey:ey-my;

	// X方ﾅﾘとY方ﾅﾘのﾋ�分のｴﾓち長い方を?離dとする
	int d=dx>=dy?dx:dy;

	// 速ﾃg(vx,vy)を?める
	vx=(mx-ex)*speed/d;
	vy=(my-ey)*speed/d;
}