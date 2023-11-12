#include <stdio.h>

// ミサイ?の各?分を表す構造体
typedef struct MISSILE_STRUCT {
	float X, Y;                   // 座標
	float VX, VY;                 // 速ﾃg
	float OldX, OldY;             // 古い座標
	float Angle;                  // 回転角ﾃg
	float OldAngle;               // 古い回転角ﾃg
	struct MISSILE_STRUCT* Prec;  // 1つ前の?分へのポイ?タ
	                              // （先蔭?分の場?にはNULL）
	bool IsMissile;               // ミサイ?かどｴﾓか
	                              // （trueならミサイ?，
	                              //   falseなら?）
} MISSILE_TYPE;

// ミサイ?の発射
void ShootMissile(
	float x, float y,   // 発射地ｼｨの座標
	int length          // ?ーザーの長さ
) {
	MISSILE_TYPE* missile;    // ミサイ?の構造体へのポイ?タ
	MISSILE_TYPE* prec=NULL;  // 1つ前の?分を指すポイ?タ
	
	// ミサイ?の各?分を作る：
	// ミサイ?の構造体を確ﾊｵ，座標を?期化する。
	// 構造体確ﾊﾌ具体的な??はNewMissileType関?で行ｴﾓとする。
	for (int i=0; i<length; i++, prec=missile) {
		missile=NewMissileType();
		missile->X=missile->OldX=x;
		missile->Y=missile->OldY=y;
		missile->Angle=missile->OldAngle=0;

		// 尾の?分は1つ前の?分を参照するよｴﾓにし，
		// 先端?分にはNULLを参照させる。
		missile->Prec=prec;

		// 先端?分はミサイ?に，他の?分は?にする。
		missile->IsMissile=(i==0);
	}
}

