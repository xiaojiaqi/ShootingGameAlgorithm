#include <math.h>

void InitCircleBullets(
	int n,                   // 弾の?
	float speed,             // 弾の速さ
	bool odd,                // 奇?パター?のとｪｽtrue
	float vx[], float vy[]   // 円形弾の速ﾃg
) {
	// 弾と弾との間の角ﾃgを計算する
	float rad_step=M_PI*2/n;

	// 最?の弾の角ﾃgを計算する：
	// 奇?パター?のとｪｽにはrad_step/2だけずらす。
	float rad=odd ? rad_step/2 : 0;

	// n個の弾の速ﾃgを?める：
	// 速さspeedで角ﾃgradの方ﾅﾘに飛ぶ弾の速ﾃgを?める。
	// 蓼れは方ﾅﾘ弾を飛ばす??の?用。
	for (int i=0; i<16; i++, rad+=rad_step) {
		vx[i]=cos(rad)*speed;
		vy[i]=sin(rad)*speed;
	}
}

