#include <math.h>

void DrawChip(int id, int x, int y);

// チｪv?（X方ﾅﾘ，Y方ﾅﾘ）
#define XMAX 20
#define YMAX 400

// 背ﾐﾞの表示
void DrawBG(
	int sx, int sy,      // 画面の?心座標
	int sw, int sh,      // 画面の大ｪｽさ
	int cw, int ch,      // チｪvの大ｪｽさ
	int map[YMAX][XMAX]  // 背ﾐﾞデータ（チｪv番?の配列）
) {
	// 回転で画面�ｯに入る背ﾐﾞの最大範ﾊ､を?める
	int w2=sw/2, h2=sh/2;            // 画面の?と?さの1/2
	int r=(int)sqrt(w2*w2+h2*h2);    // 円の半径
	int x0=(sx-r)/cw, y0=(sy-r)/ch;  // 左上端のチｪv
	int x1=(sx+r)/cw, y1=(sy+r)/ch;  // �ｸ下端のチｪv

	// チｪvの描画：
	// 各チｪvの描画はDrawChip関?で行ｴﾓとする。
	for (int i=y0; i<=y1; i++) {
		for (int j=x0; j<=x1; j++) {
			DrawChip(map[i][j], j*cw-sx+sw/2, i*ch-sy+sh/2);
		}
	}
}

