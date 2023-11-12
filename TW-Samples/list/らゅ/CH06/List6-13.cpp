// ボスを表す構造体
#define MAX_PART 32
typedef struct BOSS_STRUCT {
	float X, Y;          // ボスの座標
	struct BOSS_STRUCT* 
		Part[MAX_PART];  // ボスを構成するパーツ（ボス）
	int NumPart;         // パーツの?
	float PX[MAX_PART], 
		PY[MAX_PART];    // パーツの?､I座標
} BOSS;

void MoveBoss(BOSS* boss);

// 分離?の動ｪｽ：
// 各パーツを独立に動かす。
// 移動の具体的な??はMoveBoss関?で行ｴﾓとする。
void MoveSeparatedBoss(BOSS* boss) {
	for (int i=0; i<boss->NumPart; i++) {
		MoveBoss(boss->Part[i]);
	}
}

// ?体?の動ｪｽ：
// 全パーツｸm一体化して動くよｴﾓに，
// ?心となる座標に､Iして固ゾの位置にパーツを配置する。
// 移動の具体的な??はMoveBoss関?で行ｴﾓとする。
void MoveUnitedBoss(BOSS* boss) {
	MoveBoss(boss);
	for (int i=0; i<boss->NumPart; i++) {
		boss->Part[i]->X=boss->X+boss->PX[i];
		boss->Part[i]->Y=boss->Y+boss->PY[i];
	}
}

