void LaserCollision(
	float mx0[], float my0[],  // ���@?�[�U�[�̈�?�̍�����W
	float mx1[], float my1[],  // ���@?�[�U�[�̈�?�̅������W
	int num_my_lasers,         // ���@?�[�U�[��?����?
	float ex0[], float ey0[],  // �G?�[�U�[�̈�?�̍�����W
	float ex1[], float ey1[],  // �G?�[�U�[�̈�?�̅������W
	int num_enemy_lasers       // �G?�[�U�[��?����?
) {
	static int energy=0;        // �G�l?�M�[
	static int min_energy=100;  // �U?�̔����ɱҗv�ȃG�l?�M�[
	
	// ?�[�U�[���m��?���蔻�]??�F
	// ���@?�[�U�[�ƓG?�[�U�[�̊e?�����m�m�Ԃ�������C
	// 2��?�������ł����ăG�l?�M�[��?�₷�B
	// ���ł̋�̓I��??�́CDeleteMyLaser�C
	// DeleteEnemyLaser�̊e��?�ōs�ӂƂ���B
	for (int i=0; i<num_my_lasers; i++) {
		for (int j=0; j<num_enemy_lasers; j++) {
			if (ex0[j]<mx1[i] && mx0[i]<ex1[j] && 
				ey0[j]<my1[i] && my0[i]<ey1[j]) {
				DeleteMyLaser(i);
				DeleteEnemyLaser(j);
				energy++;
			}
		}
	}
	
	// �U?�̔����F
	// �G�l?�M�[�m�җv�ʂɒB���Ă�����C
	// �p�͂ȍU?�𔭐�������B
	// �����̋�̓I��??��SpecialAttack��?�ōs�ӂƂ���B
	if (energy>=min_energy) SpecialAttack();
}

