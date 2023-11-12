// 近接攻?に関する??
void Punch(
	bool button,               // ボタ?の状ﾆﾔ（?したとｪｽtrue）
	float px0, float py0,      // 近接攻?の左上座標
	float px1, float py1,      // 近接攻?の�ｸ下座標
	float ex0[], float ey0[],  // 敵の左上座標
	float ex1[], float ey1[],  // 敵の�ｸ下座標
	int num_enemy              // 敵の?
) {
	static bool punching=false;  // 近接攻??かどｴﾓか
	static int punch_time;       // 近接攻?を出している?間
	
	// 近接攻?の開始：
	// 近接攻??ではなく，ボタ?ｸm?されていたら，
	// 近接攻?を出す。
	if (!punching && button) {
		punching=true;
		punch_time=30;
	}
	
	// 近接攻??の??
	if (punching) {

		// 敵との?たり判ゾ??：
		// ダ?ージを与ｷVる具体的な??は，
		// DamageEnemy関?で行ｴﾓとする。
		for (int i=0; i<num_enemy; i++) {
			if (ex0[i]<px1 && px0<ex1[i] && 
				ey0[i]<py1 && py0<ey1[i]) {
				DamageEnemy(i);
			}
		}

		// 近接攻?の表示：
		// 表示の具体的な??はDrawPunch関?で行ｴﾓとする。
		DrawPunch();

		// 近接攻?の?続と終了：
		// ?続?間を過秉たら近接攻?を引っ?める。
		if (punch_time==0) punching=false; else punch_time--;
	}
}
