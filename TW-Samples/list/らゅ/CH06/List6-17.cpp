#include <stdlib.h>

void Revenge(
	float rate,          // ?ち返しの確率
	float ex, float ey,  // 敵の座標
	float tx, float ty   // 目標（自機）の座標
) {
	// 敵ｸm破壊されたかどｴﾓかの判ゾ：
	// 具体的な??はDetroyed関?で行ｴﾓとする。
	if (Destroyed()) {
	
		// ?ち返し：
		// ??を使って一ゾ確率で?ち返す。
		// ?ち返し弾は「狙い?ち弾」と同じ。
		// 発射の具体的な??はAimingBullet関?で行ｴﾓとする。
		if (rand()<=rate*RAND_MAX) {
			AimingBullet(ex, ey, tx, ty);
		}
		
		// 敵を消す：
		// 具体的な??はDelete関?で行ｴﾓとする。
		Delete();
	}
}
