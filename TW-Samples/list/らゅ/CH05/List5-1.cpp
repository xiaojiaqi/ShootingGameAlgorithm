void Bomb(
	int& bomb_time,             // ボ?の有効?間
	float x0, float y0,        // ボ?の有効範ﾊ､の左上座標
	float x1, float y1,        // ボ?の有効範ﾊ､の�ｸ下座標
	float bx0[], float by0[],  // 弾の左上座標
	float bx1[], float by1[],  // 弾の�ｸ下座標
	int num_bullet,            // 弾の?
	float ex0[], float ey0[],  // 敵の左上座標
	float ex1[], float ey1[],  // 敵の�ｸ下座標
	int num_enemy              // 敵の?
) {
	// ボ?ｸm有効な場?の??
	if (bomb_time>0) {
	
		// 弾を消す：
		// 消?の具体的な??は，
		// DeleteBullet関?で行ｴﾓとする。
		for (int i=0; i<num_bullet; i++) {
			if (bx0[i]<x1 && x0<bx1[i] && 
				by0[i]<y1 && y0<by1[i]) {
				DeleteBullet(i);
			}
		}

		// 敵にダ?ージを与ｷVる：
		// ダ?ージ付与の具体的な??は，
		// DamageEnemy関?で行ｴﾓとする。
		for (int i=0; i<num_enemy; i++) {
			if (ex0[i]<x1 && x0<ex1[i] && 
				ey0[i]<y1 && y0<ey1[i]) {
				DamageEnemy(i);
			}
		}
	
		// ボ?の有効?間を減らす
		bomb_time--;
	}
}

