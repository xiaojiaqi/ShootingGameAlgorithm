#include <math.h>

void Shot(float x, float y, float vx, float vy);

void MoveSight2(
	float& x, float& y,       // 自機の座標
	float speed,              // 自機の速さ
	bool up1, bool down1,     // 自機用スティｪN入力1（上下）
	bool left1, bool right1,  // 自機用スティｪN入力1（左�ｸ）
	float& sx, float& sy,     // 照?の座標
	float sight_speed,        // 照?の速さ
	bool up2, bool down2,     // 照?用スティｪN入力2（上下）
	bool left2, bool right2,  // 照?用スティｪN入力2（左�ｸ）
	bool button,              // シ?ｪgボタ?の入力
	float shot_speed          // シ?ｪgの速さ
) {
	// 自機を動かす
	if (up1   ) y-=speed;
	if (down1 ) y+=speed;
	if (left1 ) x-=speed;
	if (right1) x+=speed;

	// 照?を動かす
	if (up2   ) sy-=sight_speed;
	if (down2 ) sy+=sight_speed;
	if (left2 ) sx-=sight_speed;
	if (right2) sx+=sight_speed;

	// シ?ｪgを?つ：
	// シ?ｪgボタ?ｸm?されたら，
	// 自機から照?にﾅﾘかってシ?ｪgを?つ。
	// 発射の具体的な??はShot関?で行ｴﾓとする。
	if (button) {
		float vx=sx-x, vy=sy-y;
		if (vx!=0 || vy!=0) {
			float d=sqrt(vx*vx+vy*vy);
			vx*=shot_speed/d;
			vy*=shot_speed/d;
			Shot(x, y, vx, vy);
		}
	}
}

