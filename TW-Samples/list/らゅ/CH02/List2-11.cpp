#include <math.h>

// 自機の位置を格沙するテーブ?
int mpos[360][2];

// テーブ?を作る：
// M_PIは円周率。
void MakeTable() {
	for (int i=0; i<360; i++) {
		mpos[i][0]=cos(M_PI/180*i)*1000;
		mpos[i][1]=sin(M_PI/180*i)*1000;
	}
}
