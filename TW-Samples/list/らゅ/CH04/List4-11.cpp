void ShotPower(
	float& x, float& y,  // シ?ｪgの座標
	float vx, float vy,  // シ?ｪgの速ﾃg
	float& power,        // シ?ｪgの威力
	float attenuation    // 威力ｸm減?するﾃg?い
) {
	// シ?ｪgを移動させる
	x+=vx; y+=vy;
	
	// 移動するたびにシ?ｪgの威力を弱める
	power-=attenuation;
}
