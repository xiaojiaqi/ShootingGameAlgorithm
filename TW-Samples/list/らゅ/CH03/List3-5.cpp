#include <math.h>

void MoveAtConstantSpeed(
	float& x, float& y,    // 自機の座標（X方ﾅﾘ，Y方ﾅﾘ）
	float speed,           // 自機の速さ
	bool up, bool down,    // 上下方ﾅﾘへのスティｪ�ク入力
	bool left, bool right  // 左�ｸ方ﾅﾘへのスティｪ�ク入力
) {
	// 斜めに移動するとｪｽのスピード：
	// 上下左�ｸの約0.7倍にする
	float s=speed/sqrt(2);

	// 斜め移動
	if (up   && left ) x-=s, y-=s; else
	if (up   && right) x+=s, y-=s; else
	if (down && left ) x-=s, y+=s; else
	if (down && right) x+=s, y+=s; else
	
	// 上下左�ｸ移動
	if (up    && !down ) y-=speed; else
	if (down  && !up   ) y+=speed; else
	if (left  && !right) x-=speed; else
	if (right && !left ) x+=speed;
}

