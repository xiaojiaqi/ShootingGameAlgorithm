#include <math.h>

void MoveHomingBullet(
	float& x, float& y,    // 弾の座標
	float& vx, float& vy,  // 弾の速ﾃg
	float mx, float my,    // 自機の座標
	float speed,           // 弾の速さ
	float theta            // 旋回角ﾃgの上限
) {
	// 弾の元の速ﾃg
	float vx0=vx, vy0=vy;

	// 自機方ﾅﾘの速ﾃgベクト?(vx1,vy1)を?める
	float vx1, vy1;
	float d=sqrt((mx-x)*(mx-x)+(my-y)*(my-y));
	if (d) {
		vx1=(mx-x)/d*speed;
		vy1=(my-y)/d*speed;
	} else {
		vx1=0;
		vy1=speed;
	}

	// �ｸ回り旋回角ﾃg上限の速ﾃgベクト?(vx2,vy2)を?める：
	// M_PIは円周率。
	float rad=M_PI/180*theta;
	float vx2=cos(rad)*vx0-sin(rad)*vy0;
	float vy2=sin(rad)*vx0+cos(rad)*vy0;

	// 自機方ﾅﾘと旋回角ﾃg上限のどちらに曲ｸmるかを?める
	if (vx0*vx1+vy0*vy1<=vx0*vx2+vx0*vy2) {
		
		// 自機方ﾅﾘｸm旋回可能範ﾊ､�ｯの場?：
		// 自機方ﾅﾘに曲ｸmる
		vx=vx0;
		vy=vy0;

	} else {

		// 自機方ﾅﾘｸm旋回可能範ﾊ､外の場?：
		// 左回り旋回角ﾃg上限の速ﾃgベクト?(vx3,vy3)を?める
		float vx3= cos(rad)*vx0+sin(rad)*vy0;
		float vy3=-sin(rad)*vx0+cos(rad)*vy0;
		
		// 弾から自機への?､I位置ベクト?(px,py)を?める
		float px=mx-x, py=my-y;
		
		// �ｸ回りか左回りかを?める
		if (px*vx2+py*vy2<=px*vx3+py*vy3) {

			// �ｸ回りの場?
			vx=vx2;
			vy=vy2;

		} else {

			// 左回りの場?
			vx=vx3;
			vy=vy3;

		}
	}

	// 弾の座標(x,y)を更�閧ｵて，弾を移動させる
	x+=vx;
	y+=vy;
}

