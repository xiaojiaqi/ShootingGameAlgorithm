#include <math.h>

void DeleteBullet(int id);
void Shot(float x, float y, float vx, float vy);

void ReflectBullet(
	float fx0, float fy0,    // フィー?ドの左上座標
	float fx1, float fy1,    // フィー?ドの�ｸ下座標
	int num_bullet,          // 弾の?
	float x0[], float y0[],  // 弾の左上座標
	float x1[], float y1[],  // 弾の�ｸ下座標
	float x[], float y[],    // 弾の?心座標
	float ex[], float ey[],  // 弾を?った敵の?心座標
	float speed              // シ?ｪgの速さ
) {
	// 全ての弾に関して??を行ｴﾓ
	for (int i=0; i<num_bullet; i++) {
	
		// 弾とフィー?ドとの?たり判ゾ??：
		// 弾ｸmフィー?ドに接触したら，
		// 弾を消して，同じ位置から敵にﾅﾘかってシ?ｪgを?つ。
		if (fx0<x1[i] && x0[i]<fx1 && 
			fy0<y1[i] && y0[i]<fy1) {

			// 弾の消?：
			// 具体的な??はDeleteBullet関?で行ｴﾓとする。
			DeleteBullet(i);
			
			// シ?ｪgの発射：
			// 敵にﾅﾘかってシ?ｪgを?つ。
			// 発射の具体的な??はShot関?で行ｴﾓとする。
			float vx=ex[i]-x[i], vy=ey[i]-y[i];
			if (vx!=0 || vy!=0) {
				float d=sqrt(vx*vx+vy*vy);
				vx*=speed/d;
				vy*=speed/d;
				Shot(x[i], y[i], vx, vy);
			}
		}
	}
}
