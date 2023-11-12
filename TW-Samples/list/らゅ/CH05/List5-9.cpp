void MoveThrownEnemy(
	float& x0, float& y0,      // ?菷つけられた敵の左上座標
	float& x1, float& y1,      // ?菷つけられた敵の�ｸ下座標
	float vx, float vy,        // ?菷つけられた敵の速ﾃg
	float ex0[], float ey0[],  // 他の敵の左上座標
	float ex1[], float ey1[],  // 他の敵の�ｸ下座標
	int num_enemy              // 他の敵の?
) {
	// 敵との?たり判ゾ??：
	// ?菷つけられた敵と，他の全ての敵との間で
	// ?たり判ゾ??を行ｴﾓ。
	// 衝ｪwしたら，?菷つけられた敵を消し，
	// 代わりに??を出す。
	// 消滅と出現の具体的な??は，
	// DeleteEnemy，CreateExplosionの各関?で行ｴﾓとする。
	int i;
	for (i=0; i<num_enemy; i++) {
		if (ex0[i]<x1 && x0<ex1[i] && 
			ey0[i]<y1 && y0<ey1[i]) {
			DeleteEnemy(i);
			CreateExplosion(x0, y0);
		}
	}
	
	// どの敵にもぶつからなかった場?：
	// ?菷つけられた敵を動かす。
	if (i==num_enemy) {
		x0+=vx; y0+=vy;
		x1+=vx; y1+=vy;
	}
}


