#include <math.h>

void MoveSimpleHomingBullet(
	float& x, float& y,  // 弾の座標
	float mx, float my,  // 自機の座標
	float speed          // 弾の速さ
) {
	// 目標までの?離dを?める
	float d=sqrt((mx-x)*(mx-x)+(my-y)*(my-y));

	// 弾の速ﾃg(vx, vy)を?める：
	// 速さｸm一ゾ値speedになるよｴﾓにする。
	// 目標までの?離dｸm0のとｪｽには速ﾃgを下方ﾅﾘにする。
	float vx, vy;
	if (d) {
		vx=(mx-x)/d*speed;
		vy=(my-y)/d*speed;
	} else {
		vx=0;
		vy=speed;
	}

	// 弾の座標(x,y)を更して，弾を移動させる
	x+=vx;
	y+=vy;
}
