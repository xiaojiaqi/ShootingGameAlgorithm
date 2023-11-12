// チｪv?（X方ﾅﾘ，Y方ﾅﾘ）
#define XMAX 20
#define YMAX 400

// 背ﾐﾞの表示
void DrawBG(
	int sx, int sy,      // 画面左上に､I?する背ﾐﾞ上の位置
	int sw, int sh,      // 画面の大ｪｽさ
	int cw, int ch,      // チｪvの大ｪｽさ
	int map[YMAX][XMAX]  // 背ﾐﾞデータ（チｪv番?の配列）
) {
	// 描画するチｪvの範ﾊ､
	int x0=sx/cw, y0=sy/ch;                // 左上端のチｪv
	int x1=(sx+sw-1)/cw, y1=(sy+sh-1)/ch;  // �ｸ下端のチｪv

	// チｪvの描画：
	// 各チｪvの描画はDrawChip関?で行ｴﾓとする。
	for (int i=y0; i<=y1; i++) {
		for (int j=x0; j<=x1; j++) {
			DrawChip(map[i][j], j*cw-sx, i*ch-sy);
		}
	}
}

