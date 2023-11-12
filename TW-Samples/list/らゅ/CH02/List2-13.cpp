#include <math.h>

void RotateVelocity(
	float theta,           // 回転角ﾃg
	float vx0, float vy0,  // 元の速ﾃg
	float& vx, float& vy   // 回転後の速ﾃg
) {
	// thetaを?ジ･ﾂ?に変換し，cosとsinを?める：
	// M_PIは円周率。
	float rad=M_PI/180*theta;
	float c=cos(rad), s=sin(rad);

	// 速ﾃgベクト?(vx0,vy0)を回転させた(vx,vy)を?める
	vx=vx0*c-vy0*s;
	vy=vx0*s+vy0*c;
}
