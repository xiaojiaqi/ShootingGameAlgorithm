void ReinforcedShot(
	float x0, float y0,    // 自機の左上座標
	float x1, float y1,    // 自機の�ｸ下座標
	float cx0, float cy0,  // 味方機の左上座標
	float cx1, float cy1,  // 味方機の�ｸ下座標
	bool button            // シ?ｪgボタ?の状ﾆﾔ
) {
	// 味方と接近しているかどｴﾓかの判ゾ：
	// 接近している場?にはＱいシ?ｪg，
	// していない場?には通常のシ?ｪgを?つ。
	// シ?ｪgを?つ具体的な??は，
	// SpecialShot，NormalShotの各関?で行ｴﾓとする。
	if (button) {
		if (cx0<x1 && x0<cx1 && cy0<y1 && y0<cy1) {
			SpecialShot();
		} else {
			NormalShot();
		}
	}
}

