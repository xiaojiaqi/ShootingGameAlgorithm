void Slowing(
	int& gauge,  // ス?ー状ﾆﾔにするためにｱﾒ要なゲージ
	bool button  // ス?ーボタ?を?しているかどｴﾓか
) {
	// タイマー：
	// ス?ー状ﾆﾔのとｪｽに行動回?を調整するために使ｴﾓ。
	static int time=1;

	// 敵と弾を動かす：
	// 通常状ﾆﾔのとｪｽには?回動かし，
	// ス?ー状ﾆﾔのとｪｽには2回に1回だけ動かす。
	// 移動の具体的な??は，
	// MoveEnemy，MoveBulletの各関?で行ｴﾓとする。
	if (!button || (gauge>0 && time==0)) {
		MoveEnemy();
		MoveBullet();
	}
	
	// ペナ?ティ：
	// ゲージｸm0なのにス?ーボタ?を?していたら，
	// ペナ?ティとして弾をもｴﾓ1ﾃg動かす。
	// ?果として，弾は通常の2倍の速ﾃgで動く。
	if (button && gauge==0) {
		MoveBullet();
	}

	// タイマーの更
	if (time>0) time--; else time=1;
}

