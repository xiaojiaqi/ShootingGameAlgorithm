void SemiAutoShot(
	bool button,    // ボタ?の状ﾆﾔ（?されたとｪｽtrue）
	int min_power,  // 溜めパ?ーの最小値
	int max_power,  // 溜めパ?ーの最大値
	int max_gauge   // 連射ゲージの最大値
) {
	// 溜めパ?ー，連射ゲージ
	static int power=0, gauge=0;

	// ボタ?を?している場?
	if (button) {
		
		// 溜めパ?ー不足の場?：
		// 通常の弾を?つ。
		// 具体的な??はShot関?で行ｴﾓとする。
		if (power<min_power) Shot();
	
		// 溜めパ?ー�ﾏ分の場?：
		// 溜め状ﾆﾔの表示をする。
		// 具体的な??はPowerEffect関?で行ｴﾓとする。
		else PowerEffect();
	
		// 溜めパ?ーを?やし，連射ゲージを最大にする
		if (power<max_power) power++;
		gauge=max_gauge;
	}
	
	// ボタ?を離している場?：
	else {
		
		// 溜めパ?ー�ﾏ分の場?：
		// 溜め?ち弾を?つ：
		// 最大パ?ーのとｪｽは特別な弾を?つ。
		// 具体的な??はMaxShot関?とBigShot関?で行ｴﾓとする。
		if (min_power<=power) {
			if (power==max_power) MaxShot(); 
				else BigShot(power);
			gauge=0;
		}
		
		// 連射ゲージ>0の場?：
		// 通常の弾を?ち，連射ゲージを-1する。
		// 具体的な??はShot関?で行ｴﾓとする。
		if (gauge>0) {
			Shot();
			gauge--;
		}

		// 溜めパ?ーを0にする
		power=0;
	}
}
