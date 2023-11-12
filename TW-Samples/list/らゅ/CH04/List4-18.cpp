#include <math.h>

void TurnMarker(
	float& x, float& y,     // 自機の座標
	float speed,            // 自機の速さ
	bool left, bool right,  // スティｪNの状ﾆﾔ（左�ｸ方ﾅﾘ）
	bool up, bool down,     // スティｪNの状ﾆﾔ（上下方ﾅﾘ）
	bool turn_button,       // 旋回ボタ?の状ﾆﾔ
	bool shot_button        // シ?ｪgボタ?の状ﾆﾔ
) {
	static bool turning;        // 旋回?ならばtrue
	static float mx, my;        // ター?マーｧｼーの座標
	static float rad=M_PI*3/2;  // 旋回角ﾃg（M_PIは円周率）
	static float d=10;          // 自機とター?マーｧｼーの?離
	
	// 旋回の開始：
	// ター?マーｧｼーの座標を算出する。
	if (!turning && turn_button) {
		turning=true;
		mx=x-d*cos(rad);
		my=y-d*sin(rad);
	}
	
	// 旋回の終了
	if (!turn_button) turning=false;
	
	// 自機の移動
	if (up   ) y-=speed;
	if (down ) y+=speed;
	if (left ) x-=speed;
	if (right) x+=speed;
	
	// 旋回?ならば旋回角ﾃgを計算する
	if (turning) rad=-atan2(x-mx, y-my);
	
	// シ?ｪgの発射：
	// 自機ｸmﾅﾘいている方ﾅﾘにシ?ｪgを?つ。
	// 発射方ﾅﾘはradとは反､I方ﾅﾘ（180?=π?ジ･ﾂ?ずれる）。
	// 発射の具体的な??はDirectedShot関?で行ｴﾓとする。
	if (shot_button) DirectedShot(x, y, rad+M_PI);
}

