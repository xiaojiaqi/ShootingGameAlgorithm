void MoveAimingBulletFP(
	int& x, int& y,  // 弾の座標
	int vx, int vy   // 弾の速ﾃg
) {
	// 弾の座標(x,y)に速ﾃg(vx,vy)を加ｷVる
	x+=vx;
	y+=vy;

	// 弾を描く：
	// 画面に弾を描くとｪｽには座標を(x>>8, y>>8)とする。
	// 弾を描く具体的な??はDraw関?で行ｴﾓとする。
	Draw(x>>8, y>>8);
}