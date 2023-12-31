#include <math.h>

void InitDirectedBulletDDA(
	int theta,         // 発射角ﾃg
	int ex, int ey,    // 敵の座標
	int& x, int& y,    // 弾の座標
	int& vx, int& vy,  // 弾の移動方ﾅﾘ
	int& dx, int& dy,  // X方ﾅﾘとY方ﾅﾘのﾋ�分
	int& diff          // 誤ﾋ�
) {
	// 仮想的な自機を?くに配置する：
	// M_PIは円周率。
	int mx=cos(M_PI/180*theta)*1000;
	int my=sin(M_PI/180*theta)*1000;

	// ?とはDDAを使った狙い?ち弾の??と同じ

	// 弾の座標を設ゾする
	x=ex; y=ey;

	// 弾の移動方ﾅﾘ(vx,vy)を?める：値は1または-1
	vx=mx>ex?1:-1;
	vy=my>ey?1:-1;

	// 目標に､IするX方ﾅﾘとY方ﾅﾘのﾋ�分の絶､I値(dx,dy)を?める
	dx=mx>=ex?mx-ex:ex-mx;
	dy=my>=ey?my-ey:ey-my;

	// 誤ﾋ�diff：dx>=dyのとｪｽはdx/2，dx<dyのとｪｽはdy/2とする
	diff=dx>=dy?dx/2:dy/2;
}

