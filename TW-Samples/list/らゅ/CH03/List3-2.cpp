void MoveMyShip2(
	float& x, float& y,    // 自機の座標（X方ﾅﾘ，Y方ﾅﾘ）
	float speed,           // 自機の速さ
	float x0, float y0,    // 自機の左上座標
	float x1, float y1,    // 自機の�ｸ下座標
	float sx0, float sy0,  // 移動可能枠の左上座標
	float sx1, float sy1,  // 移動可能枠の�ｸ下座標
	bool up, bool down,    // 上下方ﾅﾘへのスティｪ�ク入力
	bool left, bool right  // 左�ｸ方ﾅﾘへのスティｪ�ク入力
) {
	if (up    && sy0<=y0) y-=speed;
	if (down  && y1<=sy1) y+=speed;
	if (left  && sx0<=x0) x-=speed;
	if (right && x1<=sx1) x+=speed;
}
