void SpeedControlByItem(
	float& speed,          // スピード
	float max_speed,       // 最?速
	float min_speed,       // 最低速
	float x0, float y0,    // 拾い判ゾの左上座標
	float x1, float y1,    // 拾い判ゾの�ｸ下座標
	float ix0, float iy0,  // ･ﾂイテ?の?たり判ゾの左上座標
	float ix1, float iy1,  // ･ﾂイテ?の?たり判ゾの�ｸ下座標
	float accel            // スピード･ﾂｪv・ダウ?のﾃg?い
) {
	// ･ﾂイテ?を拾ったとｪｽの??：
	// ?たり判ゾ??を行い，?たったとｪｽには，
	// スピード･ﾂｪvまたはスピードダウ?を行ｴﾓ。
	if (ix0<x1 && x0<ix1 && iy0<y1 && y0<iy1) {
		speed+=accel;
		
		// 以下のよｴﾓにすると，
		// スピードダウ?を1個拾っただけで，
		// スピードｸm最低になるよｴﾓにでｪｽる。
		// if (accel<0) speed=min_speed;
		
		// スピードｸm最?速や最低速を超ｷVたら補正する
		if (speed>max_speed) speed=max_speed;
		if (speed<min_speed) speed=min_speed;
	}
}
