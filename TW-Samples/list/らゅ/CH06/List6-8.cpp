#include <stdlib.h>

// 敵の間隔
#define INTERVAL 6

// 敵の情報（構造体）
typedef struct ENEMY_STRUCT {
	float X, Y;                 // 現在の座標
	float OldX[INTERVAL];       // 古いX座標
	float OldY[INTERVAL];       // 古いY座標
	int Index;                  // 最も古い座標を指すイ?デｪNス
	struct ENEMY_STRUCT* Prec;  // 1つ前の敵
} ENEMY;
// 荊ﾇ�飛行の??
void Formation(
	int num_enemy,  // 敵の?
	ENEMY* enemy[]  // 敵の情報（構造体へのポイ?タ）
) {
	// 敵を動かす
	int i;
for (i=0; i<num_enemy; i++) {
		ENEMY* self=enemy[i];
		ENEMY* prec=self->Prec;
		
		// 先蔭以外の敵を動かす：
		// 1つ前の敵ｸmﾊｶしている古い座標のｴﾓち，
		// もっとも古いものを自分の座標にする。
		if (prec) {
			self->X=prec->OldX[prec->Index];
			self->Y=prec->OldY[prec->Index];
		}
		
		// 先蔭の敵を動かす：
		// 具体的な??はMoveEnemy関?で行ｴﾓとする。
		else {
			MoveEnemy(i);
		}
	}

	// 古い座標を記録する：
	// 最も古い座標をしい座標で上?ｪｽし，
	// イ?デｪNスを更する。
	for (i=0; i<num_enemy; i++) {
		ENEMY* self=enemy[i];
		self->OldX[self->Index]=self->X;
		self->OldY[self->Index]=self->Y;
		self->Index=(self->Index+1)%INTERVAL;
	}
}
