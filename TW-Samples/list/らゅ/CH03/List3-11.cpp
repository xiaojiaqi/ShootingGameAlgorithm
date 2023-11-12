// 自機の状ﾆﾔ（歩行，上昇，下降）
typedef enum {
	WALKING, JUMP_UP, JUMP_DOWN
} MYSHIP_STATE;

// 自機の動ｪｽ
void Walk(
	float& x, float& y,     // 自機の座標
	float speed,            // 自機の速さ
	bool left, bool right,  // スティｪN入力（左�ｸ）
	bool jump_button        // ジ??プボタ?の入力
) {
	static MYSHIP_STATE state=WALKING;  // 自機の状ﾆﾔ
	static int time;                    // ジ??プの?間
	
	// 左�ｸへの移動
	if (left ) x-=speed;
	if (right) x+=speed;

	// 状ﾆﾔによって分岐する
	switch (state) {

		// 歩行：
		// ジ??プボタ?を?したら上昇状ﾆﾔに移行する。
		case WALKING:
			if (jump_button) {
				state=JUMP_UP;
				time=40;
			}
			break;
		
		// 上昇：
		// 一ゾ?間上昇したら下降状ﾆﾔに移行する。
		case JUMP_UP:
			y-=speed;
			if (time==0) {
				state=JUMP_DOWN;
				time=40;
			} else time--;
			break;
		
		// 下降：
		// 一ゾ?間下降したら歩行状ﾆﾔに戻る。
		case JUMP_DOWN:
			y+=speed;
			if (time==0) state=WALKING; else time--;
			break;
	}
}
