void PowerShot(
	bool button,    // ボタ?の状ﾆﾔ（?されたとｪｽtrue）
	int min_power,  // 弾ｸm出る最小のパ?ー
	int max_power   // 最大のパ?ー
) {
	// 溜めパ?ー
	static int power=0;

	// ボタ?を?している場?：
	// 溜めパ?ーを?やす。
	if (button && power<max_power) power++;
	
	// ボタ?を離している場?：
	// 溜めパ?ー>0ならば弾を?ち，溜めパ?ーを0に戻す。
	if (!button && power>0) {
		
		// 最大パ?ーのとｪｽ：
		// 特別な弾を?つ。
		// 具体的な??はMaxShot関?で行ｴﾓとする。
		if (power==max_power) MaxShot(); else
		
		// 最小パ?ー以上，最大パ?ー未?のとｪｽ：
		// 溜めパ?ーに?じたＱさの溜め?ち弾を?つ。
		// 具体的な??はBigShot関?で行ｴﾓとする。
		if (min_power<=power) BigShot(power);
		
		// 溜めパ?ーを0に戻す
		power=0;

	}
}
