void LockShot(
	bool button,     // ボタ?の状ﾆﾔ（?されたとｪｽtrue）
	int min_power,   // 溜めパ?ーの最小値
	int max_gauge,   // 連射ゲージの最大値
	int enemy_id,    // ?ｪ�クシ?ｪ�トｸm追尾している敵のID
	                 // （追尾していないとｪｽには?の値）
	float front_dir  // 自機の正面に??する方ﾅﾘ
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
		// 連射ゲージを0にして，?ｪ�クシ?ｪ�トを?つ。
		else {
			gauge=0;
			
			// ?ｪ�クシ?ｪ�トを?つ：
			// 敵を追尾しているとｪｽは敵を狙い?ちする。
			// （「自機にﾅﾘかって飛ぶ弾」と同様）
			// 敵を追尾していないとｪｽは自機の正面に弾を?つ。
			// （「自由な方ﾅﾘに飛ぶ弾」と同様）
			// それぞれ具体的な??はAimingShot関?と
			// DirectedShot関?で行ｴﾓとする。
			if (enemy_id>=0) {
				AimingShot(enemy_id);
			} else {
				DirectedShot(front_dir);
			}
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
