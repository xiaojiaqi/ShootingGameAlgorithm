void MoveAcceleratedBullet(
	float speed,          // 弾の速さ
	float accel,          // 加速ﾃg
	float& vx, float& vy  // 速ﾃgのX成分とY成分
) {
	// 速ﾃgを古い速さで?る
	if (speed!=0) {
		vx/=speed; vy/=speed;
	}

	// 速さを更�閧ｷる
	speed+=accel;

	// 速ﾃgに�閧ｵい速さを掛ける
	vx*=speed; vy*=speed;
}