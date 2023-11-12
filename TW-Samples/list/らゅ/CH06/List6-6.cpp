void OrbitalFlight(
	int num_enemy,           // 敵の?
	float ex[], float ey[],  // 敵の座標
	int index[],             // 軌道データを指すイ?デｪ�クス
	int num_orbit,           // 軌道データの要素?
	float ox[], float oy[]   // 軌道データ（座標）
) {
	for (int i=0; i<num_enemy; i++) {
		
		// 敵座標の更�閨F
		// 軌道データをﾃｯみ出して，敵の�閧ｵい座標とする。
		ex[i]=ox[index[i]];
		ey[i]=oy[index[i]];
		
		// イ?デｪ�クス（データのﾃｯみ出し位置）を進める：
		// 軌道データの最後に達したら敵を消す。
		// 敵を消す具体的な??はDeleteEnemy関?で行ｴﾓとする。
		// 
		index[i]++;
		if (index[i]==num_orbit) DeleteEnemy(i);
	}
}
