// �G�̃^�C�v��\���]?�F
// �j��Ū���C�j��Ū��Ȃ��C?��m?����Ȃ�
typedef enum {
	BREAKABLE, UNBREAKABLE, TRANSPARENT
} ENEMY_TYPE;

// �j��Ū��Ȃ����̂��؂߂��G��??
void BreakableEnemy2(
	int num_enemy,             // �G��?
	ENEMY_TYPE type[],         // �G�̃^�C�v
	float ex0[], float ey0[],  // �G��?���蔻�]�̍�����W
	float ex1[], float ey1[],  // �G��?���蔻�]�̅������W
	float vit[],               // �G�̑ϋv��
	int num_weapon,            // ?���?
	float wx0[], float wy0[],  // ?���?���蔻�]�̍�����W
	float wx1[], float wy1[],  // ?���?���蔻�]�̅������W
	float str[]                // ?��̍U?��
) {
	// �S�Ă̓G�Ɋւ���?�[�v
	for (int i=0; i<num_enemy; i++) {
		
		// ?���?����Ȃ��G�̏�?�F
		// ?���蔻�]??�͍s�킸�C
		// ?�̓G��??�Ɉڂ�B
		if (type[i]==TRANSPARENT) continue;
		
		// �G��?��Ƃ�?���蔻�]??
		for (int j=0; j<num_weapon; j++) {
			if (ex0[i]<wx1[j] && wx0[j]<ex1[i] && 
				ey0[i]<wy1[j] && wy0[j]<ey1[i]
			) {
				// �j��Ū���G��?��������?�F
				// ?��̍U?�͂œG�̑ϋv�͂����C
				// �ϋv�͸m0�܂���?�ɂȂ�����G��j�󂷂�B
				// �j��̋�̓I��??�́C
				// DeleteEnemy��?�ōs�ӂƂ���B
				if (type[i]==BREAKABLE) {
					vit[i]-=str[j];
					if (vit[i]<=0) DeleteEnemy(i);
				}
				
				// �G��?������?��͏����F
				// ��̓I��??��DeleteWeapon��?�ōs�ӂƂ���B
				DeleteWeapon(j);
			}
		}
	}
}
