void Enemy(
	int num_enemy,             // 敵の?
	float ex0[], float ey0[],  // 敵の?たり判ゾの左上座標
	float ex1[], float ey1[],  // 敵の?たり判ゾの�ｸ下座標
	float sx0, float sy0,      // 移動可能枠（画面枠）の左上座標
	float sx1, float sy1       // 移動可能枠（画面枠）の�ｸ下座標
) {
	for (int i=0; i<num_enemy; i++) {
		
		// 敵の移動：
		// 移動の具体的な??はDeleteEnemy関?で行ｴﾓとする。
		MoveEnemy(i);
		
		// 敵の消失：
		// 敵ｸm画面枠から出たかどｴﾓかを判ゾし，
		// 出ていたら消す。
		// 消失の具体的な??はDeleteEnemy関?で行ｴﾓとする。
		if (ex1[i]<=sx0 || sx1<=ex0[i] || 
			ey1[i]<=sy0 || sy1<=ey0[i]) {
			DeleteEnemy(i);
		}
	}
}

