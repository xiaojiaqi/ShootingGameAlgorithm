void MoveGroundMissile(
	float& x0, float& y0,      // ミサイ?の左上座標
	float& x1, float& y1,      // ミサイ?の�ｸ下座標
	float vx, float vy,        // ミサイ?の速ﾃg（?平，?直）
	float gx0[], float gy0[],  // 地形の左上座標
	float gx1[], float gy1[],  // 地形の�ｸ下座標
	int num_ground,            // 地形の?
	float ex0[], float ey0[],  // 敵の左上座標
	float ex1[], float ey1[],  // 敵の�ｸ下座標
	int num_enemy              // 敵の?
) {
	// 地形との?たり判ゾ??：
	// ミサイ?を?直方ﾅﾘに進めた座標について，
	// 地形に?たるかどｴﾓかを判ゾする。
	// 地形に?たった場?には，?直方ﾅﾘの速ﾃgを0にして，
	// ?ープから抜ける。
	for (int i=0; i<num_ground; i++) {
		if (gx0[i]<x1 && x0<gx1[i] && 
			gy0[i]<y1+vy && y0+vy<gy1[i]) {
			vy=0;
			break;
		}
	}
	
	// ミサイ?を進める
	x0+=vx; y0+=vy;
	x1+=vx; y1+=vy;

	// 敵との?たり判ゾ??：
	// 敵に?たった場?には，敵にダ?ージを与ｷVて，
	// ?ープから抜ける。
	// ダ?ージの具体的な??はDamageEnemy関?で行ｴﾓとする。
	for (int i=0; i<num_enemy; i++) {
		if (ex0[i]<x1 && x0<ex1[i] && 
			ey0[i]<y1 && y0<ey1[i]) {
			DamageEnemy(i);
			break;
		}
	}
}
