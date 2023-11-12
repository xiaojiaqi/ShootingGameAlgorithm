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

// ?ーザーの発射
void ShootHomingLaser(
	float x, float y,   // 発射地ｼｨの座標
	int length          // ?ーザーの長さ
) {
	LASER_TYPE* laser;      // ?ーザーを表す構造体へのポイ?タ
	LASER_TYPE* prec=NULL;  // 1つ前の?分を指すポイ?タ
	
	// ?ーザーの各?分を作る：
	// ?ーザーの構造体を確ﾊｵ，座標を?期化する。
	// 構造体確ﾊﾌ具体的な??はNewLaserType関?で行ｴﾓとする。
	for (int i=0; i<length; i++, prec=laser) {
		laser=NewLaserType();
		laser->X=laser->OldX=x;
		laser->Y=laser->OldY=y;
		laser->Angle=laser->OldAngle=0;

		// 尾の?分は1つ前の?分を参照するよｴﾓにし，
		// 先端?分にはNULLを参照させる。
		laser->Prec=prec;
	}
}

