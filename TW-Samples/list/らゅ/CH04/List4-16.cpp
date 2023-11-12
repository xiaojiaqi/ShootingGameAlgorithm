// ?ーザーの各?分を表す構造体
typedef struct LASER_STRUCT {
	float X, Y;                 // 左上座標
	float W, H;                 // ?と?さ
	float VX, VY;               // 速ﾃg
	float OldX, OldY;           // 古い座標
	struct LASER_STRUCT* Prec;  // 1つ前の?分
	                            // （先蔭?分の場?にはNULL）
} LASER_TYPE;

// ?ーザーを動かす関?
void MoveReflectLaser(
	LASER_TYPE* laser,         // ?ーザーの1つの?分
	float gx0[], float gy0[],  // 地形の左上座標
	float gx1[], float gy1[],  // 地形の�ｸ下座標
	int num_ground             // 地形の?
) {
	// 先端?分の場?：
	// 地形で反射するシ?ｪgの??と同じ。
	if (!laser->Prec) {

		// 地形との?たり判ゾ??：
		// 先端?分を?直方ﾅﾘに進めた座標(X, Y+VY)について，
		// 地形に?たるかどｴﾓかを判ゾする。
		// 地形に?たった場?には，?直方ﾅﾘの速ﾃgをﾊ艪ﾉして，
		// ?ープから抜ける。
		for (int i=0; i<num_ground; i++) {
			if (gx0[i]<laser->X+laser->W &&
				laser->X<gx1[i] && 
				gy0[i]<laser->Y+laser->W+laser->VY &&
				laser->Y+laser->VY<gy1[i]
			) {
				laser->VX=-laser->VX;
				break;
			}
		}

		// 先端?分を進める
		laser->X+=laser->VX;
		laser->Y+=laser->VY;
	}
	
	// 先端?分以外の場?：
	// 1つ前の?分を追いかける。
	// 1つ前の?分の古い座標へ移動する。
	else {
		laser->X=laser->Prec->OldX;
		laser->Y=laser->Prec->OldY;
	}
}

