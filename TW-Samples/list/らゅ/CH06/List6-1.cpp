void BreakableEnemy(
	int num_enemy,             // 敵の?
	float ex0[], float ey0[],  // 敵の?たり判ゾの左上座標
	float ex1[], float ey1[],  // 敵の?たり判ゾの�ｸ下座標
	float vit[],               // 敵の耐久力
	int num_weapon,            // ?器の?
	float wx0[], float wy0[],  // ?器の?たり判ゾの左上座標
	float wx1[], float wy1[],  // ?器の?たり判ゾの�ｸ下座標
	float str[]                // ?器の攻?力
) {
	// 敵と?器の?たり判ゾ??：
	// 全ての敵と?器の組み?わせについて，
	// ?器ｸm敵に?たったかどｴﾓかを判ゾする
	for (int i=0; i<num_enemy; i++) {
		for (int j=0; j<num_weapon; j++) {
			if (ex0[i]<wx1[j] && wx0[j]<ex1[i] && 
				ey0[i]<wy1[j] && wy0[j]<ey1[i]
			) {
				// ?たった場?：
				// ?器の攻?力で敵の耐久力を削り，
				// 耐久力ｸm0または?になったら敵を破壊する。
				// 破壊の具体的な??は，
				// DeleteEnemy関?で行ｴﾓとする。
				vit[i]-=str[j];
				if (vit[i]<=0) DeleteEnemy(i);
				
				// 敵に?たった?器は消す：
				// 具体的な??はDeleteWeapon関?で行ｴﾓとする。
				DeleteWeapon(j);
			}
		}
	}
}

