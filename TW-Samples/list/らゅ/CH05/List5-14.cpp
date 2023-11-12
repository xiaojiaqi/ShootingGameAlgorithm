void ReinforcedShot3(
	float sx0, float sy0,  // シ?ｪgの左上座標
	float sx1, float sy1,  // シ?ｪgの�ｸ下座標
	float cx0, float cy0,  // 味方の左上座標
	float cx1, float cy1   // 味方の�ｸ下座標
) {
	// シ?ｪgと味方との?たり判ゾ??：
	// ?たったとｪｽにはシ?ｪgを消し，
	// 代わりにＱいシ?ｪgを出す。
	// 具体的な??は，
	// DeleteShot，SpecialShotの各関?で行ｴﾓとする。
	// シ?ｪgを消さずに，
	// シ?ｪgのＱさだけを変ｷVる方法も?る。
	if (cx0<sx1 && sx0<cx1 && cy0<sy1 && sy0<cy1) {
		DeleteShot();
		SpecialShot();
	}
}

