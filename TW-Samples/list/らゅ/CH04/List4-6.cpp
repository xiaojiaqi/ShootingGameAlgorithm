void ShotAndLaser(
	bool button,    // ボタ?の状ﾆﾔ（?されたとｪｽtrue）
	int min_power,  // 溜めパ?ーの最小値
	int max_gauge   // 連射ゲージの最大値
) {
	// 溜めパ?ー，連射ゲージ
	static int power=0, gauge=0;

	// ボタ?を?している場?
	if (button) {
		
		// 溜めパ?ー不足の場?：
		// 溜めパ?ーを?やし，連射ゲージを最大にして，
		// 弾を?つ。具体的な??はShot関?で行ｴﾓとする。
		if (power<min_power) {
			power++;
			gauge=max_gauge;
			Shot();
		}
	
		// 溜めパ?ー�ﾏ分の場?：
		// 連射ゲージを0にして，?ーザーを?つ。
		// 具体的な??はLaser関?で行ｴﾓとする。
		else {
			gauge=0;
			Laser();
		}
	}
	
	// ボタ?を離している場?：
	else {
		
		// 連射ゲージ>0の場?：
		// ?通の弾を?ち，連射ゲージを-1する。
		if (gauge>0) {
			Shot();
			gauge--;
		}

		// 溜めパ?ーを0にする
		power=0;
	}
}
