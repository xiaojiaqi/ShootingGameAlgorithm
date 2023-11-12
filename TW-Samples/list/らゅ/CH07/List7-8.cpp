void ScrollSpeed(
	int y,               // 自機のY座標
	int& svy,            // スク?ー?の速ﾃg（Y方ﾅﾘ）
	int ymin, int ymax,  // 自機Y座標の最大値，最小値
	int smax, int smin   // スク?ー?の最大，最小スピード
) {
	svy=smin+(y-ymin)*(smax-smin)/(ymax-ymin);
}