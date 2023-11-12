#include <math.h>

void InitAimingBullet(
	float mx, float my,   // 自機の座標
	float ex, float ey,   // 敵の座標
	float speed,          // 弾の速さ
	float& x, float& y,   // 弾の座標
	float& vx, float& vy  // 弾の速ﾃg
) {
	// 弾の座標を設ゾする
	x=ex; y=ey;

	// 目標までの?離dを?める
	float d=sqrt((mx-ex)*(mx-ex)+(my-ey)*(my-ey));

	// 速さｸm一ゾ値speedになるよｴﾓに速ﾃg(vx,vy)を?める：
	// 目標までの?離dｸm0のとｪｽには下方ﾅﾘに発射する。
	if (d) {
		vx=(mx-ex)/d*speed;
		vy=(my-ey)/d*speed;
	} else {
		vx=0;
		vy=speed;
	}
}