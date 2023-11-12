void MoveThrownShip(
	float& x0, float& y0,  // 機体の左上座標
	float& x1, float& y1,  // 機体の�ｸ下座標
	float& vx, float& vy,  // 機体の速ﾃg
	float sx0, float sy0,  // 移動可能範ﾊ､（画面枠）の左上座標
	float sx1, float sy1   // 移動可能範ﾊ､（画面枠）の�ｸ下座標
) {
	// 跳ね回る動ｪｽのための??：
	// 画面枠の上下左�ｸからはみ出しそｴﾓになったら，
	// 移動速ﾃgをﾊ艪ﾉする。
	if (x0+vx<sx0 || sx1<=x1+vx) vx=-vx;
	if (y0+vy<sy0 || sy1<=y1+vy) vy=-vy;
	
	// 機体を移動させる
	x0+=vx; x1+=vx;
	y0+=vy; y1+=vy;
}

