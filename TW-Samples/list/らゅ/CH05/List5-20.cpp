// 状ﾆﾔ（通常，照?，攻?）
typedef enum {
	NORMAL, SIGHT, ATTACK
} STATE_TYPE;

// 自機と照?を動かす
void MoveSight1(
	float& x, float& y,     // 自機の座標
	float& sx, float& sy,   // 照?の座標
	float speed,            // 自機の移動の速さ
	float sight_speed,      // 照?の移動の速さ
	bool up, bool down,     // スティｪN入力（上下）
	bool left, bool right,  // スティｪN入力（左�ｸ）
	bool button             // 照?ボタ?入力
) {
	static int state=NORMAL;  // 状ﾆﾔ（通常から開始）
	static int time;          // 攻??間
	
	// 状ﾆﾔに?じて分岐する
	switch (state) {
	
		// 通常状ﾆﾔ：
		// 自機を移動し，
		// ボタ?ｸm?されたら照?を出して，照?状ﾆﾔに移る。
		case NORMAL:
			if (up   ) y-=speed;
			if (down ) y+=speed;
			if (left ) x-=speed;
			if (right) x+=speed;
			if (button) {
				state=SIGHT;
				sx=x; sy=y;
			}
			break;
		
		// 照?状ﾆﾔ：
		// 照?を移動し，ボタ?ｸm離されたら攻?状ﾆﾔに移る。
		case SIGHT:
			if (up   ) sy-=sight_speed;
			if (down ) sy+=sight_speed;
			if (left ) sx-=sight_speed;
			if (right) sx+=sight_speed;
			if (!button) {
				state=ATTACK;
				time=100;
			}
			break;
		
		// 攻?状ﾆﾔ：
		// 自機を移動し，一ゾ?間ｸm経ったら通常状ﾆﾔに戻る。
		case ATTACK:
			if (up   ) y-=speed;
			if (down ) y+=speed;
			if (left ) x-=speed;
			if (right) x+=speed;
			if (time==0) state=NORMAL;
			time--;
			break;
	}
}

