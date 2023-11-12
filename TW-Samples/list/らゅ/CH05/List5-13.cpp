#include <math.h>

void SpecialShot(float x, float y, float vx, float vy);

void ReinforcedShot2(
	float x, float y,    // 自機の座標
	float cx, float cy,  // 味方機の座標
	float speed          // シ?ｪgの速さ
) {
	// シ?ｪgの速ﾃgを?める
	float vx=x-cx, vy=y-cy;
	float d=sqrt(vx*vx+vy*vy);
	vx*=speed/d;
	vy*=speed/d;

	// シ?ｪgを発射する：
	// 発射の具体的な??はSpecialShot関?で行ｴﾓとする。
	SpecialShot(x, y, vx, vy);
}

