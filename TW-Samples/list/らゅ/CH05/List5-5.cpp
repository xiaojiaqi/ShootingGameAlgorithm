void Invincible(
	bool invincible,           // 無敵状ﾆﾔならばtrue
	float x0, float y0,        // 自機の左上座標
	float x1, float y1,        // 自機の�ｸ下座標
	float ex0[], float ey0[],  // 敵の左上座標
	float ex1[], float ey1[],  // 敵の左上座標
	int num_enemy,             // 敵の?
	float bx0[], float by0[],  // 弾の左上座標
	float bx1[], float by1[],  // 弾の左上座標
	int num_bullet             // 弾の?
) {
	// 敵との?たり判ゾ??：
	// 敵とぶつかった場?，無敵状ﾆﾔならば敵にダ?ージを与ｷV，
	// 通常状ﾆﾔならばミスとする。
	// ダ?ージ付与とミスの具体的な??は，
	// DamageEnemy，Missの各関?で行ｴﾓとする。
	for (int i=0; i<num_enemy; i++) {
		if (ex0[i]<x1 && x0<ex1[i] && 
			ey0[i]<y1 && y0<ey1[i]) {
			if (invincible) DamageEnemy(i); else Miss();
		}
	}
	
	// 弾との?たり判ゾ??：
	// 弾とぶつかった場?，無敵状ﾆﾔならば弾を消し，
	// 通常状ﾆﾔならばミスとする。
	// 消?とミスの具体的な??は，
	// DeleteBullet，Missの各関?で行ｴﾓとする。
	for (int i=0; i<num_bullet; i++) {
		if (bx0[i]<x1 && x0<bx1[i] && 
			by0[i]<y1 && y0<by1[i]) {
			if (invincible) DeleteBullet(i); else Miss();
		}
	}
}
