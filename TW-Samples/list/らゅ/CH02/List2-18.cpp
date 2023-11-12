#include <stdio.h>

// ?ーザーの各?分を表す構造体
typedef struct LASER_STRUCT {
	float X, Y;                 // 座標
	float VX, VY;               // 速ﾃg
	float OldX, OldY;           // 古い座標
	float Angle;                // 回転角ﾃg
	float OldAngle;             // 古い回転角ﾃg
	struct LASER_STRUCT* Prec;  // 1つ前の?分へのポイ?タ
	                            // （先蔭?分の場?にはNULL）
} LASER_TYPE;


// ?ーザーを動かす関?
void MoveHomingLaser(
	LASER_TYPE* laser  // ?ーザーの先蔭?分または尾の1?分
) {
	// 先端?分の場?：
	// 誘導弾の動ｪｽと同じ。
	// 誘導の具体的な??はMoveHoming関?で行ｴﾓとする。
	if (laser->Prec==NULL) {
		MoveHoming(laser);
	}

	// 先端?分以外の場?：
	// 1つ前の?分を追いかける。
	// 古い座標と古い回転角ﾃgをコピーする。
	else {
		laser->X=laser->Prec->OldX;
		laser->Y=laser->Prec->OldY;
		laser->Angle=laser->Prec->OldAngle;
	}
}
