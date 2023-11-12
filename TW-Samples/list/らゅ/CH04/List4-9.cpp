void DeleteShot();

void MoveShot(
	float& x0, float& y0,  // シ?ｪgの左上座標
	float& x1, float& y1,  // シ?ｪgの�ｸ下座標
	float vx, float vy,    // シ?ｪgの速ﾃg（X方ﾅﾘ，Y方ﾅﾘ）
	float sx0, float sy0,  // 画面枠の左上座標
	float sx1, float sy1   // 画面枠の�ｸ下座標
) {
	// シ?ｪgｸm画面外に出ていたら消す：
	// 具体的な??はDeleteShot関?で行ｴﾓとする。
	if (x1<=sx0 || sx1<=x0 || y1<=sy0 || sy1<=y0) DeleteShot();

	// シ?ｪgを移動する（座標を更する）
	x0+=vx; y0+=vy;
	x1+=vx; y1+=vy;
}