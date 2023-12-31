void Warp(
	float& x, float& y,    // 自機の座標
	float speed,           // 自機の移動速ﾃg
	float warp_dist,       // ?ープの移動?離
	bool up, bool down,    // スティｪ�ク入力（上下）
	bool left, bool right  // スティｪ�ク入力（左�ｸ）
) {
	static bool 
		up0=false, down0=false,     // 前回のスティｪ�ク入力
		left0=false, right0=false,  // （上下，左�ｸ）
		released=true;              // 無入力状ﾆﾔにしたかどｴﾓか
	static int time=0;              // 入力の制限?間

	// スティｪ�クｸm入力されたとｪｽ
	if (up || down || left || right) {
		
		// ?ープする場?：
		// 無入力をはさんで，かつ制限?間�ｯに，
		// 前回と同じ方ﾅﾘｸm入力されたとｪｽ。
		if (released && time>0 &&
			up==up0 && down==down0 &&
			left==left0 && right==right0
		) {
			if (up   ) y-=warp_dist;
			if (down ) y+=warp_dist;
			if (left ) x-=warp_dist;
			if (right) x+=warp_dist;
		}
		
		// ?ープしない場?：
		// 無入力をはさんでいないか，制限?間切れか，
		// 前回と異なる方ﾅﾘｸm入力されたとｪｽ。
		// 方ﾅﾘを記録し，制限?間を設ゾする。
		else {
			up0=up; down0=down;
			left0=left; right0=right;
			time=10;
			
			// ?通に移動する
			if (up   ) y-=speed;
			if (down ) y+=speed;
			if (left ) x-=speed;
			if (right) x+=speed;
		}

		released=false;
	}
	
	// スティｪ�クｸm無入力状ﾆﾔのとｪｽ
	else released=true;
	
	// ?間を減らす
	if (time>0) time--;
}

