// ?器を切り替ｷVる??
void SelectWeapon(
	bool button  // ボタ?の状ﾆﾔ（?したとｪｽtrue）
) {
	static int weapon_id=0;         // 現在選択?の?器の番?
	static bool prev_button=false;  // 前回のボタ?の状ﾆﾔ
	
	// ?器を切り替ｷVる：
	// 前回ボタ?を?してｯuらず，今回?していたら，
	// ?器の切り替ｷVを行ｴﾓ。
	if (!prev_button && button) {
		weapon_id=(weapon_id+1)%MAX_WEAPONS;
	}
	
	// ?器の･ﾂイコ?を表示する：
	// 全･ﾂイコ?を表示し，選択?の･ﾂイコ?は目立たせる。
	// 表示の具体的な??はDrawIcon関?とFocusIcon関?で
	// 行ｴﾓとする。
	for (int i=0; i<MAX_WEAPONS; i++) DrawIcon(i);
	FocusIcon(weapon_id);

	// 今回のボタ?の状ﾆﾔをﾊｶする
	prev_button=button;
}


