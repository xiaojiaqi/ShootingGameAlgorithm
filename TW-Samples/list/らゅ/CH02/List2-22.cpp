void MoveDroppingBullet(
	float& x, float& y,   // 弾の座標
	float accel,          // 加速ﾃg
	float& vx, float& vy  // 速ﾃgのX成分とY成分
) {
	// 速ﾃgを更する：
	// X成分は変化させず，Y成分だけを変化させる。
	vy+=accel;

	// 座標を更する
	x+=vx; y+=vy;
}