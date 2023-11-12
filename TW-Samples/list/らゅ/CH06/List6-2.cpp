// 敵のタイプを表すゾ?：
// 破壊でｪｽる，破壊でｪｽない，?器ｸm?たらない
typedef enum {
	BREAKABLE, UNBREAKABLE, TRANSPARENT
} ENEMY_TYPE;

// 破壊でｪｽないものもﾏﾘめた敵の??
void BreakableEnemy2(
	int num_enemy,             // 敵の?
	ENEMY_TYPE type[],         // 敵のタイプ
	float ex0[], float ey0[],  // 敵の?たり判ゾの左上座標
	float ex1[], float ey1[],  // 敵の?たり判ゾの�ｸ下座標
	float vit[],               // 敵の耐久力
	int num_weapon,            // ?器の?
	float wx0[], float wy0[],  // ?器の?たり判ゾの左上座標
	float wx1[], float wy1[],  // ?器の?たり判ゾの�ｸ下座標
	float str[]                // ?器の攻?力
) {
	// 全ての敵に関する?ープ
	for (int i=0; i<num_enemy; i++) {
		
		// ?器に?たらない敵の場?：
		// ?たり判ゾ??は行わず，
		// ?の敵の??に移る。
		if (type[i]==TRANSPARENT) continue;
		
		// 敵と?器との?たり判ゾ??
		for (int j=0; j<num_weapon; j++) {
			if (ex0[i]<wx1[j] && wx0[j]<ex1[i] && 
				ey0[i]<wy1[j] && wy0[j]<ey1[i]
			) {
				// 破壊でｪｽる敵に?たった場?：
				// ?器の攻?力で敵の耐久力を削り，
				// 耐久力ｸm0または?になったら敵を破壊する。
				// 破壊の具体的な??は，
				// DeleteEnemy関?で行ｴﾓとする。
				if (type[i]==BREAKABLE) {
					vit[i]-=str[j];
					if (vit[i]<=0) DeleteEnemy(i);
				}
				
				// 敵に?たった?器は消す：
				// 具体的な??はDeleteWeapon関?で行ｴﾓとする。
				DeleteWeapon(j);
			}
		}
	}
}
