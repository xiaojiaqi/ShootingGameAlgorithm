#include <math.h>

void MoveLoopingBullet2(
	float& x, float& y,    // 弾の座標
	float& vx, float& vy,  // 弾の速ﾃg
	float cx, float cy,    // 回転?心の座標
	float& r,              // 半径
	float vr,              // 半径の変化
	float theta,           // 角ﾃg（?ジ･ﾂ?）
	float omega            // 1回の移動で変化する角ﾃg（?ジ･ﾂ?）
) {
	// 角ﾃgを変化させる
	theta+=omega;
	
	// 半径を変化させる
	r+=vr;

	// 位置を計算する
	x=cx+r*cos(theta);
	y=cy+r*sin(theta);

	// 弾の速ﾃg（ｱﾒ要な場?だけ）
	vx=-r*omega*sin(theta);
	vy= r*omega*cos(theta);
}
