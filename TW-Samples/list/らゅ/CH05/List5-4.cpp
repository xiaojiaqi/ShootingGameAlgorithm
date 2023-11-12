void ItemSpecialAttack(
	float x0, float y0,        // 自機の左上座標
	float x1, float y1,        // 自機の�ｸ下座標
	float ix0[], float iy0[],  // ･ﾂイテ?の左上座標
	float ix1[], float iy1[],  // ･ﾂイテ?の左上座標
	int num_item               // ･ﾂイテ?の?
) {
	static bool special=false;  // 今の状ﾆﾔｸm特殊ならばtrue
	static int time;            // 特殊攻?の残り?間
	
	// 通常状ﾆﾔのとｪｽ
	if (!special) {

		// 通常攻?を行ｴﾓ：
		// 具体的な??はNormalAttack関?で行ｴﾓとする。
		NormalAttack();
		
		// ･ﾂイテ?を拾ったかどｴﾓかの判ゾ：
		// 拾ったら特殊状ﾆﾔに移り，残り?間を設ゾする。
		for (int i=0; i<num_item; i++) {
			if (ix0[i]<x1 && x0<ix1[i] && 
				iy0[i]<y1 && y0<iy1[i]) {
				special=true;
				time=300;
			}
		}
	}
	
	// 特殊状ﾆﾔのとｪｽ
	else {
		
		// 特殊攻?を行ｴﾓ：
		// 具体的な??はSpecialAttack関?で行ｴﾓとする。
		SpecialAttack();
		
		// 一ゾ?間ｸm過秉たかどｴﾓかの判ゾ：
		// 残り?間ｸmなくなったら通常状ﾆﾔに戻る。
		if (time==0) special=false; else time--;
	}
}

