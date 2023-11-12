// 味方の状ﾆﾔ（捕捉，?遊，?体）
typedef enum {
	CAPTURED, FLOATING, DOCKED
} DOCKING_STATE;

// ?体に関する??
void Docking(
	float& cx, float& cy,  // 味方の座標
	float ex, float ey,    // 敵の座標
	float mx, float my,    // 自機の座標
	DOCKING_STATE& state   // 味方の状ﾆﾔ
) {
	// 味方の状ﾆﾔによって分岐する
	switch (state) {
		
		// 捕捉：
		// 敵と一?に動く。
		// 敵ｸm破壊されたら?遊状ﾆﾔに移行する。
		// 敵の破壊判ゾ??はEnemyDestroyed関?で行ｴﾓとする。
		case CAPTURED:
			cx=ex; cy=ey;
			if (EnemyDestroyed()) state=FLOATING;
			break;
		
		// ?遊：
		// 自由に動く。
		// 蓼蓼では画面下方ﾅﾘに直進するとする。
		// 自機に接触したら?体状ﾆﾔに移行する。
		// 接触判ゾ??はCatched関?で行ｴﾓとする。
		case FLOATING:
			cy++;
			if (Catched()) state=DOCKED;
			break;
		
		// ?体：
		// 自機と一?に動く。
		case DOCKED:
			cx=mx; cy=my;
			break;
	}
}
