// チｪv?（X方ﾅﾘ，Y方ﾅﾘ）
#define XMAX 1000
#define YMAX 50

// 上下左�ｸｸmつなｸmった背ﾐﾞの表示
void DrawCirculatedBG(
	int sx, int sy,      // 画面左上に､I?する背ﾐﾞ上の位置
	int sw, int sh,      // 画面の大ｪｽさ
	int cw, int ch,      // チｪvの大ｪｽさ
	int map[XMAX][YMAX]  // 背ﾐﾞデータ（チｪv番?の配列）
) {
	// 描画するチｪvの範ﾊ､
	int x0=sx/cw, y0=sy/ch;    // 左上端のチｪv
	int x1=(sx+sw-1)/cw%XMAX, 
		y1=(sy+sh-1)/ch%YMAX;  // �ｸ下端のチｪv

	// チｪvの描画：
	// 各チｪvの描画はDrawChip関?で行ｴﾓとする。
	for (int i=x0; i!=x1+1; i=(i+1)%XMAX) {
		for (int j=y0; j!=y1+1; j=(j+1)%YMAX) {
			DrawChip(map[i][j], j*cw-sx, i*ch-sy);
		}
	}
}
