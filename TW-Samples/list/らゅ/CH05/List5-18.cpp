void GrazeBullet(
	float gx0, float gy0,    // かすり判ゾの左上座標
	float gx1, float gy1,    // かすり判ゾの�ｸ下座標
	int num_bullet,          // 弾の?
	float x0[], float y0[],  // 弾の?たり判ゾの左上座標
	float x1[], float y1[],  // 弾の?たり判ゾの�ｸ下座標
	bool grazing[],          // 弾ｸmかすっているかどｴﾓか
	int time[],              // かすり?間
	int& power               // 自機のパ?ー
	                         // （経験値，ｱﾓｼｨ倍率など）
) {
	// 全ての弾について??を行ｴﾓ
	for (int i=0; i<num_bullet; i++) {

		// 通常状ﾆﾔ：
		// ?たり判ゾ??を行い，弾ｸm自機にかすったら，
		// かすり状ﾆﾔにする。
		// かすり状ﾆﾔの残り?間を設ゾし，自機のパ?ーを?やす。
		if (!grazing[i]) {
			if (gx0<x1[i] && x0[i]<gx1 && 
				gy0<y1[i] && y0[i]<gy1) {
				grazing[i]=true;
				time[i]=20;
				power++;
			}
		}
		
		// かすり状ﾆﾔ：
		// かすり状ﾆﾔの残り?間を減らし，
		// ?間ｸm0になったら通常状ﾆﾔに戻る。
		// 蓼の??をなくせば，1つの弾に1ﾃgしかかすれなくなる。
		else {
			if (time[i]==0) grazing[i]=false; else time[i]--;
		}
	}
	
}
