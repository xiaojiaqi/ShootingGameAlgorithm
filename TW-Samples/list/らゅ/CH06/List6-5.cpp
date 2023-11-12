void MoveFixedBattery(
	int num_enemy,           // 敵（固ゾ砲台）の?
	float ex[], float ey[],  // 敵（固ゾ砲台）の座標
	float svx, float svy     // 背ﾐﾞの移動速ﾃg（スク?ー?速ﾃg）
) {
	// 全ての固ゾ砲台を背ﾐﾞと同じ速ﾃgで動かす
	for (int i=0; i<num_enemy; i++) {
		ex[i]+=svx;
		ey[i]+=svy;
	}
}