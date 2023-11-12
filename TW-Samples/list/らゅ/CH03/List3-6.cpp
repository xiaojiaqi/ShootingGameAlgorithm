void MoveByAnalog(
	float& x, float& y,    // 自機の座標（X方ﾅﾘ，Y方ﾅﾘ）
	float speed,           // 自機の最?速ﾃg
	int jx, int jy,        // スティｪNの入力値（X方ﾅﾘ，Y方ﾅﾘ）
	int range, int margin  // 入力値の範ﾊ､（最大値），マージ?
) {
	// X方ﾅﾘに関する移動
	if (jx<=-range+margin) x-=speed; else
	if (+range-margin<=jx) x+=speed; else
	if (jx<-margin) x+=speed*(jx+margin)/(range-margin*2); else
	if (+margin<jx) x+=speed*(jx-margin)/(range-margin*2);
	
	// Y方ﾅﾘに関する移動
	if (jy<=-range+margin) y-=speed; else
	if (+range-margin<=jy) y+=speed; else
	if (jy<-margin) y+=speed*(jy+margin)/(range-margin*2); else
	if (+margin<jy) y+=speed*(jy-margin)/(range-margin*2);
}