void InducedExplosion(
	float ex0[], float ey0[],  // 敵の左上座標
	float ex1[], float ey1[],  // 敵の�ｸ下座標
	int num_enemy,             // 敵の?
	float x0[], float y0[],    // ??の左上座標
	float x1[], float y1[],    // ??の�ｸ下座標
	int num_explosion          // ??の?
) {
	// 敵と??の?たり判ゾ??：
	// 全ての敵と??との間で?たり判ゾ??を行い，
	// 敵ｸm??に?たったら破壊する。
	// そして敵と同じ座標にたな??を生成する。
	// 破壊と生成の具体的な??は，
	// DestroyEnemy，CreateExplosionの各関?で行ｴﾓとする。
	for (int i=0; i<num_enemy; i++) {
		for (int j=0; j<num_explosion; j++) {
			if (ex0[i]<x1[j] && x0[j]<ex1[i] && 
				ey0[i]<y1[j] && y0[j]<ey1[i]) {
				DestroyEnemy(i);
				CreateExplosion(ex0[i], ey0[i]);
			}
		}
	}
}
