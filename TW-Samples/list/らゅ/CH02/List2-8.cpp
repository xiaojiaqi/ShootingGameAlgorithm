void MoveDirectedBullet(
	float& x, float& y,  // 弾の座標
	float vx, float vy   // 弾の速ﾃg
) {
	// 弾の座標(x,y)に速ﾃg(vx,vy)を加ｷVる
	x+=vx;
	y+=vy;
}
