void SpeedControlByButton(
	float& speed,     // スピード
	float accel,      // スピード･ﾂｪvのﾃg?い
	float max_speed,  // 最?速
	float min_speed,  // 最低速
	bool button       // 速ﾃg調節ボタ?の入力
) {
	// 前回のボタ?の状ﾆﾔ
	static bool prev_button=false;
	
	// ボタ?を一ﾃg離して?した場?：
	// 速ﾃg調節を行ｴﾓ。
	if (!prev_button && button) {
		if (speed>=max_speed) speed=min_speed;
		else speed+=accel;
	}
	
	// ボタ?の状ﾆﾔを記録する
	prev_button=button;
}
