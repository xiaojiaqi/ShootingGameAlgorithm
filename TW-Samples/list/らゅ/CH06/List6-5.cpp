void MoveFixedBattery(
	int num_enemy,           // �G�i�Ń]�C��j��?
	float ex[], float ey[],  // �G�i�Ń]�C��j�̍��W
	float svx, float svy     // �w�ނ̈ړ����g�i�X�N?�[?���g�j
) {
	// �S�Ă̌Ń]�C���w�ނƓ������g�œ�����
	for (int i=0; i<num_enemy; i++) {
		ex[i]+=svx;
		ey[i]+=svy;
	}
}