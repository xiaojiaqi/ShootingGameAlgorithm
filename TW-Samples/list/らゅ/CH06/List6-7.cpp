void OrbitalFlight(
	int num_enemy,           // �G��?
	float ex[], float ey[],  // �G�̍��W
	int index[],             // �O���f�[�^���w���C?�f��N�X
	int num_orbit,           // �O���f�[�^�̗v�f?
	float ox[], float oy[]   // �O���f�[�^�i���W�j
) {
	for (int i=0; i<num_enemy; i++) {
		
		// �G���W�̍X��F
		// �O���f�[�^��ï�ݏo���āC�G���肵�����W�Ƃ���B
		ex[i]=ox[index[i]];
		ey[i]=oy[index[i]];
		
		// �C?�f��N�X�i�f�[�^��ï�ݏo���ʒu�j��i�߂�F
		// �O���f�[�^�̍Ō�ɒB������G�������B
		// �G��������̓I��??��DeleteEnemy��?�ōs�ӂƂ���B
		// 
		index[i]++;
		if (index[i]==num_orbit) DeleteEnemy(i);
	}
}

