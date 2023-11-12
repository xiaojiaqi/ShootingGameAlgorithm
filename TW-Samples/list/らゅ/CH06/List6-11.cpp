// 敵を表す構造体
typedef struct {
	float X, Y;  // 敵の座標
} ENEMY;

// ボス（複雑な構造の敵）を表す構造体
#define MAX_PART 32
typedef struct {
	float X, Y;             // ボスの座標
	ENEMY* Part[MAX_PART];  // ボスを構成するパーツ（敵）
	int NumPart;            // パーツ（敵）の?
	bool Fatal[MAX_PART];   // 致命的なパーツかどｴﾓか
} COMPLEX_ENEMY;

void MoveEnemy(ENEMY* enemy);
void DrawEnemy(ENEMY* enemy, float x, float y);
bool Destroyed(ENEMY* enemy);
void DeleteEnemy(ENEMY* enemy);
void DeleteEnemy(COMPLEX_ENEMY* enemy);

// ボスの動ｪｽ：
// ボスを構成する全ての敵について?に??を行ｴﾓ。
void MoveComplexEnemy(COMPLEX_ENEMY* ce) {
	for (int i=0; i<ce->NumPart; i++) {

		// 敵の行動：
		// 具体的な??はMoveEnemy関?で行ｴﾓとする。
		MoveEnemy(ce->Part[i]);

		// 敵の描画：
		// 全てのパーツを一体化させて動かすために，
		// パーツの座標をボス座標からの?､I位置として使ｴﾓ。
		// ボス全体を動かすにはce->Xとce->Yを変更する。
		// 具体的な??はDrawEnemy関?で行ｴﾓとする。
		DrawEnemy(ce->Part[i],
			ce->Part[i]->X+ce->X, ce->Part[i]->Y+ce->Y);

		// 敵の破壊：
		// 判ゾと破壊の具体的な??は，
		// Destroyed，DeleteEnemyの各関?で行ｴﾓとする。
		if (Destroyed(ce->Part[i])) {
			DeleteEnemy(ce->Part[i]);

			// ボス全体の破壊：
			// 破壊されたパーツｸm致命的だったとｪｽには，
			// ボス全体を破壊する。
			if (ce->Fatal[i]) DeleteEnemy(ce);
		}
	}
}

