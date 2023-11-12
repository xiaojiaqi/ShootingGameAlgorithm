void OverlaidScroll(
	int num_bg,           // 背ﾐﾞの?
	int sx[], int sy[],   // 各背ﾐﾞ上の表示位置
	int svx[], int svy[]  // 各背ﾐﾞのスク?ー?速ﾃg
) {
	// 全背ﾐﾞの描画：
	// 各背ﾐﾞの表示位置を?に更した後に表示する。
	// 表示の具体的な??はDrawBG関?で行ｴﾓとする。
	for (int i=0; i<num_bg; i++) {
		sx[i]+=svx[i];
		sy[i]+=svy[i];
		DrawBG(i);
	}
}
