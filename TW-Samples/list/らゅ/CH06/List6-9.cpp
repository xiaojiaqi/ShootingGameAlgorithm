#include <stdlib.h>

// 敵の情報（構造体）
typedef struct ENEMY_STRUCT {
	float X, Y;                 // 現在の座標
	float OldX[INTERVAL];       // 古いX座標
	float OldY[INTERVAL];       // 古いY座標
	int Index;                  // 最も古い座標を指すイ?デｪ�クス
	struct ENEMY_STRUCT* Prec;  // 1つ前の敵
} ENEMY;

// 荊ﾇ�の生成
void eFormation(
	float x, float y,  // 生成地ｼｨの座標
	int count          // 荊ﾇ�を構成する敵の?
) {
	ENEMY* enemy;      // 敵を表す構造体へのポイ?タ
	ENEMY* prec=NULL;  // 1つ前の敵を指すポイ?タ
	
	// 荊ﾇ�を構成する敵を作る：
	// 敵の構造体を確ﾊ�し，座標を?期化する。
	// 構造体確ﾊ�の具体的な??はNewEnemyType関?で行ｴﾓとする。
	for (int i=0; i<count; i++, prec=enemy) {
		enemy=NewEnemyType();
		enemy->X=x;
		enemy->Y=y;
		for (int j=0; j<INTERVAL; j++) {
			enemy->OldX[j]=x;
			enemy->OldY[j]=y;
		}
		enemy->Index=0;

		// 先蔭以外の敵は1つ前の敵を参照し，
		// 先端の敵はNULLを参照する。
		enemy->Prec=prec;
	}
}

