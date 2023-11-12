// 敵を表す構造体
typedef struct {
	bool Locked;  // ?ｪNされているかどｴﾓか
	float X, Y;   // 座標
} ENEMY_TYPE;
#define MAX_ENEMIES 100
static ENEMY_TYPE Enemy[MAX_ENEMIES];

bool Hit(float x, float y, ENEMY_TYPE& enemy);
void ShootLockOnLaser(ENEMY_TYPE& enemy);

// ?ｪNオ?の使用可能?
static int AvailLocks=8;

// ?ｪNオ??ーザーの発射
void LockOnLaser(
	float sx, float sy,  // 照?の座標
	bool button          // ボタ?の状ﾆﾔ（?されたとｪｽtrue）
) {
	// ?ｪNオ?の使用可能?ｸm1以上のとｪｽ：
	// 全ての敵と照?との?たり判ゾ??を行い，
	// 照?と重なった敵には?ｪNマークを付ける。
	// ?たり判ゾの具体的な??はHit関?で行ｴﾓとする。
	for (int i=0; AvailLocks>0 && i<MAX_ENEMIES; i++) {
		if (!Enemy[i].Locked && Hit(sx, sy, Enemy[i])) {
			Enemy[i].Locked=true;

			// ?ｪNオ?の使用可能?を減らす：
			// 敵に?ーザーｸm命?したら，使用可能?を?やす。
			AvailLocks--;
		}
	}

	// ボタ?ｸm?された場?：
	// ?ｪNマークｸm付いた全ての敵にﾅﾘけて?ーザーを発射する。
	// 発射の具体的な??はShootLockOnLaser関?で行ｴﾓとする。
	if (button) {
		for (int i=0; i<MAX_ENEMIES; i++) {
			if (Enemy[i].Locked) ShootLockOnLaser(Enemy[i]);
		}
	}
}

