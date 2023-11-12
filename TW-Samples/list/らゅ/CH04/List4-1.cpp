void Shot();

void BasicShot(
	bool button  // 今回のボタ?の状ﾆﾔ（?されたとｪｽtrue）
) {
	// 前回のボタ?の状ﾆﾔ（?されたとｪｽtrue）
	static bool prev_button=false;
	
	// シ?ｪgの発射：
	// 前回ボタ?ｸm?されてｯuらず，今回?されているとｪｽだけ，
	// シ?ｪgを発射する。
	// 発射の詳細な??はShot関?で行ｴﾓものとする。
	if (!prev_button && button) Shot();
	
	// 今回のボタ?の状ﾆﾔをﾊｶする
	prev_button=button;
}
