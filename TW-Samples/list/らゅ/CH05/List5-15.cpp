void SwitchColors(
	bool color_button,   // 色切り替ｷVボタ?の状ﾆﾔ
	bool shot_button,    // シ?ｪgボタ?の状ﾆﾔ
	int num_bullet,      // 弾の?
	bool bullet_color[]  // 弾の色
) {
	static bool prev_col_button=false;  // 前回のボタ?の状ﾆﾔ
	static bool color=true;             // 自機の色
	static int energy=0;                // エネ?ギー
	
	// 色を切り替ｷVる
	if (!prev_col_button && color_button) color=~color;
	prev_col_button=color_button;
	
	// シ?ｪgを?つ：
	// 自機と同じ色のシ?ｪgを?つ。
	// シ?ｪgの具体的な??はShot関?で行ｴﾓとする。
	if (shot_button) Shot(color);
	
	// 弾との?たり判ゾ??：
	// 判ゾの具体的な??はHitBullet関?で行ｴﾓとする。
	for (int i=0; i<num_bullet; i++) {
		if (HitBullet(i)) {
			
			// 同じ色ならば吸収：
			// 弾を消し，エネ?ギーを?やす。
			// 消?の具体的な??はDeleteBullet関?で行ｴﾓとする。
			if (color==bullet_color[i]) {
				DeleteBullet(i);
				energy++;
			}
			
			// 異なる色ならばミス：
			// ミスの具体的な??はMiss関?で行ｴﾓとする。
			else {
				Miss();
			}
		}
	}
}

