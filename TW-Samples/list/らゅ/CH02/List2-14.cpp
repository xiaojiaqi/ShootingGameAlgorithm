#include <math.h>

void InitNWayBullets(
	float vx0, float vy0,    // ?心となる弾の速ﾃg
	float theta,             // 弾と弾の間の角ﾃg
	int n,                   // 弾の?
	float vx[], float vy[]   // n-way弾の速ﾃg
) {
	// 弾と弾の間の角ﾃgを?ジ･ﾂ?に変換する
	float rad_step=M_PI/180*theta;
	
	// 端の弾と?心の弾との間の角ﾃgを計算する
	float rad=n%2 ? -n/2*rad_step : (-n/2+0.5)*rad_step;

	// n個の弾の速ﾃgを計算する
	for (int i=0; i<n; i++, rad+=rad_step) {
		
		// (vx[i],vy[i])を?める：
		// 速ﾃgベクト?(vx0,vy0)をradだけ回転させる。
		float c=cos(rad), s=sin(rad);
		vx[i]=vx0*c-vy0*s;
		vy[i]=vx0*s+vy0*c;
	}
}
