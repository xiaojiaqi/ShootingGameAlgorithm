void Underwater2(
	float& x, float& y,        // 自機の座標
	float x0, float y0,        // 自機の左上座標
	float x1, float y1,        // 自機の�ｸ下座標
	float vx, float vy,        // 自機の速ﾃg
	float wx0[], float wy0[],  // ?の?たり判ゾ
	float wx1[], float wy1[],  // （左上座標，�ｸ下座標）
	int num_water              // ?の?たり判ゾの?
) {
	// 自機ｸm??にいるかどｴﾓかを調べる
	int i;
	for (i=0; i<num_water; i++) {
		if (wx0[i]<=x0 && x1<=wx1[i] && 
			wy0[i]<=y0 && y1<=wy1[i]) break;
	}
	
	// 自機ｸm??にいる場?：
	// 速ﾃgをΦくする。蓼蓼では空?の半分とした。
	if (i<num_water) {
		x+=vx/2; y+=vy/2;
	}
	
	// 自機ｸm??にはいない場?：
	// 通常の速ﾃgで移動する
	else {
		x+=vx; y+=vy;
		
		// 自機ｸm?面に接触しているかどｴﾓかを調べる
		for (i=0; i<num_water; i++) {
			if (wx0[i]<x1 && x0<wx1[i] && 
				wy0[i]<y1 && y0<wy1[i]) break;
		}

		// 自機ｸm?面に接触している場?：
		// 波しぶｪｽなどのエフェクトを表示する。
		// 具体的な??はWaveEffect関?で行ｴﾓとする。
		if (i<num_water) WaveEffect();
	}
}

