void Shot();

void BasicShot(
	bool button  // 今回のボタ?の状ﾆﾔ（?されたとｪｽtrue）
) {
	// 前回のボタ?の状ﾆﾔ（?されたとｪｽtrue）
	static bool prev_button=false;
	
	// シ?ｪ�トの発射：
	// 前回ボタ?ｸm?されてｯuらず，今回?されているとｪｽだけ，
	// シ?ｪ�トを発射する。
	// 発射の詳細な??はShot関?で行ｴﾓものとする。
	if (!prev_button && button) Shot();
	
	// 今回のボタ?の状ﾆﾔをﾊ�存する
	prev_button=button;
}
