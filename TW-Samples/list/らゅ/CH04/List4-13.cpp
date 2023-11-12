// �G��\���\����
typedef struct {
	bool Locked;  // ?��N����Ă��邩�Ǵӂ�
	float X, Y;   // ���W
} ENEMY_TYPE;
#define MAX_ENEMIES 100
static ENEMY_TYPE Enemy[MAX_ENEMIES];

bool Hit(float x, float y, ENEMY_TYPE& enemy);
void ShootLockOnLaser(ENEMY_TYPE& enemy);

// ?��N�I?�̎g�p�\?
static int AvailLocks=8;

// ?��N�I??�[�U�[�̔���
void LockOnLaser(
	float sx, float sy,  // ��?�̍��W
	bool button          // �{�^?�̏��ԁi?���ꂽ�ƪ�true�j
) {
	// ?��N�I?�̎g�p�\?�m1�ȏ�̂ƪ��F
	// �S�Ă̓G�Ə�?�Ƃ�?���蔻�]??���s���C
	// ��?�Əd�Ȃ����G�ɂ�?��N�}�[�N��t����B
	// ?���蔻�]�̋�̓I��??��Hit��?�ōs�ӂƂ���B
	for (int i=0; AvailLocks>0 && i<MAX_ENEMIES; i++) {
		if (!Enemy[i].Locked && Hit(sx, sy, Enemy[i])) {
			Enemy[i].Locked=true;

			// ?��N�I?�̎g�p�\?�����炷�F
			// �G��?�[�U�[�m��?������C�g�p�\?��?�₷�B
			AvailLocks--;
		}
	}

	// �{�^?�m?���ꂽ��?�F
	// ?��N�}�[�N�m�t�����S�Ă̓G���؂���?�[�U�[�𔭎˂���B
	// ���˂̋�̓I��??��ShootLockOnLaser��?�ōs�ӂƂ���B
	if (button) {
		for (int i=0; i<MAX_ENEMIES; i++) {
			if (Enemy[i].Locked) ShootLockOnLaser(Enemy[i]);
		}
	}
}

