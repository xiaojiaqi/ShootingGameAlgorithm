void MixedScroll(
	int x, int y,  // 自機の背ﾐﾞ上の座標
	int w,         // 自機の?
	int sy,        // スク?ー?位置のY座標
	int svy,       // Y方ﾅﾘのスク?ー?速ﾃg
	int sw,        // 画面?
	int bw         // 背ﾐﾞの?
) {
	// 背ﾐﾞの描画：
	// スク?ー?位置を更し，背ﾐﾞを描画する。
	// 描画の具体的な??はDrawBG関?で行ｴﾓとする。
	int sx=(bw-sw)*x/(bw-w);
	sy+=svy;
	DrawBG(sx, sy);
	
	// 自機の描画：
	// スク?ー?位置からの?､I位置に表示する。
	// 描画の具体的な??はDrawMyShip関?で行ｴﾓとする。
	DrawMyShip(x-sx, y-sy);
}

