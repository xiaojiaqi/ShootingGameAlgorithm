void WaveEffect();

void Underwater1(
	float& x, float& y,  // 自機の座標
	float vx, float vy,  // 自機の速ﾃg
	float h              // ?面の?さ
) {
	// 空?の場?：
	// 通常の速ﾃgで移動する。
	if (y<h) {
		x+=vx; y+=vy;
	}

	// ??の場?：
	// 速ﾃgをΦくする。蓼蓼では空?の半分とした。
	else {
		x+=vx/2; y+=vy/2;
	}
}
