void Shot();

void AutoShot(
	bool button  // ボタ?の状ﾆﾔ（?されたとｪｽtrue）
) {
	// シ?ｪ�トの発射：
	// ボタ?ｸm?されていたらシ?ｪ�トを発射する。
	// 発射の詳細な??はShot関?で行ｴﾓものとする。
	if (button) Shot();
}
