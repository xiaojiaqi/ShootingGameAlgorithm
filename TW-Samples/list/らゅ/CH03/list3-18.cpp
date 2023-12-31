void Barrier2(
	float x0, float y0,        // バ?･ﾂの?たり判ゾ
	float x1, float y1,        // （左上座標，�ｸ下座標）
	float bx0[], float by0[],  // 弾の?たり判ゾ
	float bx1[], float by1[],  // （左上座標，�ｸ下座標）
	int num_bullet,            // 弾の?
	float ex0[], float ey0[],  // 敵の?たり判ゾ
	float ex1[], float ey1[],  // （左上座標，�ｸ下座標）
	int num_enemy,             // 敵の?
	int& energy,               // バ?･ﾂのエネ?ギー
	bool barrier_button        // バ?･ﾂボタ?の状ﾆﾔ
) {
	// バ?･ﾂを張る：
	// バ?･ﾂボタ?ｸm?されてｯuり，
	// かつエネ?ギーｸm?るとｪｽには，バ?･ﾂを張る。
	if (barrier_button && energy>0) {
	
		// バ?･ﾂと弾との?たり判ゾ??：
		// 弾ｸm?たったら，弾を消し，バ?･ﾂのエネ?ギーを減らす。
		// 弾を消す具体的な??はDeleteBullet関?で行ｴﾓとする。
		for (int i=0; i<num_bullet && energy>0; i++) {
			if (bx0[i]<x1 && x0<bx1[i] && 
				by0[i]<y1 && y0<by1[i]) {
				DeleteBullet(i);
				energy--;
			}
		}

		// バ?･ﾂと敵との?たり判ゾ??：
		// 敵ｸm?たったら，敵にダ?ージを与ｷV，
		// バ?･ﾂのエネ?ギーを減らす。
		// 敵にダ?ージを与ｷVる具体的な??は，
		// DamageEnemy関?で行ｴﾓとする。
		for (int i=0; i<num_enemy && energy>0; i++) {
			if (ex0[i]<x1 && x0<ex1[i] && 
				ey0[i]<y1 && y0<ey1[i]) {
				DamageEnemy(i);
				energy--;
			}
		}

		// エネ?ギーの消費
		energy--;
	}
}


