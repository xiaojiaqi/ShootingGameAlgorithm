void HitShot(
	float x0, float y0,    // シ?ｪgの?たり判ゾの左上座標
	float x1, float y1,    // シ?ｪgの?たり判ゾの�ｸ下座標
	float attack,          // シ?ｪgの攻?力
	float ox0, float oy0,  // ､I象の?たり判ゾの左上座標
	float ox1, float oy1,  // ､I象の?たり判ゾの�ｸ下座標
	float endurance,       // ､I象の耐久力
	bool invincible        // ､I象ｸm破壊不可能かどｴﾓか
) {
	// シ?ｪgｸm､I象に?たった場?
	if (ox0<x1 && x0<ox1 && oy0<y1 && y0<oy1) {

		// ､I象ｸm無敵でない場?：
		// シ?ｪgの攻?力で､I象の耐久力を削り，
		// 耐久力ｸm0になったら､I象を消す。
		// 具体的な??はDeleteOpponent関?で行ｴﾓとする。
		if (!invincible) {
			endurance-=attack;
			if (endurance<0) DeleteOpponent();
		}
		
		// シ?ｪgを消す：
		// 具体的な??はDeleteShot関?で行ｴﾓとする。
		// 蓼蓼でシ?ｪgを消さないと，貫通弾になる。
		DeleteShot();
	}
}

