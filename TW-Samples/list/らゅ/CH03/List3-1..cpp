void MoveMyShip(
	float& x, float& y,    // 自機の座標（X方ﾅﾘ，Y方ﾅﾘ）
	float speed,           // 自機の速さ
	bool up, bool down,    // 上下方ﾅﾘへのスティｪN入力
	bool left, bool right  // 左�ｸ方ﾅﾘへのスティｪN入力
) {
	if (up   ) y-=speed;
	if (down ) y+=speed;
	if (left ) x-=speed;
	if (right) x+=speed;
}