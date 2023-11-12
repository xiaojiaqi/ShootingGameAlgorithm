// オプシ??の?期化
void InitOption(
	float x, float y,        // 自機の座標（X方ﾅﾘ，Y方ﾅﾘ）
	float ox[], float oy[],  // 自機の古い座標（配列）
	int length               // 古い座標の個?（配列の長さ）
) {
	// 配列の全要素を自機の座標で?期化する
	for (int i=0; i<length; i++) {
		ox[i]=x; oy[i]=y;
	}
}

// オプシ??の移動
void MoveOption(
	float x, float y,        // 自機の座標（X方ﾅﾘ，Y方ﾅﾘ）
	float ox[], float oy[],  // 自機の古い座標（配列）
	int length,              // 古い座標の?（配列の長さ）
	int& index,              // 座標のﾊｶ位置（配列上の位置）
	int opt_count,           // オプシ??の個?
	int opt_interval         // オプシ??の間隔（配列上の間隔）
) {
	// オプシ??を描く：
	// DrawOptionはオプシ??を描く関?とする
	for (int c=0, i=index; c<opt_count; c++) {
		i=(i-opt_interval+length)%length;
		DrawOption(ox[i], oy[i]);
	}
	
	// 自機の座標をﾊｶし，座標のﾊｶ位置を更する
	ox[index]=x;
	oy[index]=y;
	index=(index+1)%length;
}

