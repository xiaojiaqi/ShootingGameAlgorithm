// 自機の形ﾆﾔ（歩行，飛行）
typedef enum {
	WALKING, FLYING
} MYSHIP_FORM;

// 自機の変形
void Transform(
	bool button  // 変形ボタ?の入力
) {
	static MYSHIP_FORM formation=WALKING;  // 自機の形ﾆﾔ
	static bool prev_button=false;         // 前回のボタ?入力
	
	// 変形：
	// 変形ボタ?ｸm?されたら変形する。
	if (!prev_button && button) {
		if (formation==WALKING) formation=FLYING;
			else formation=WALKING;
	}
	prev_button=button;
	
	// 形ﾆﾔによって動ｪｽを変ｷVる：
	// 具体的な??はWalk，Flyの各関?で行ｴﾓとする。
	if (formation==WALKING) Walk(); else Fly();
}

