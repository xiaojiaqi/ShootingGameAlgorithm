void GrazeBullet(
	float gx0, float gy0,    // �����蔻�]�̍�����W
	float gx1, float gy1,    // �����蔻�]�̅������W
	int num_bullet,          // �e��?
	float x0[], float y0[],  // �e��?���蔻�]�̍�����W
	float x1[], float y1[],  // �e��?���蔻�]�̅������W
	bool grazing[],          // �e�m�������Ă��邩�Ǵӂ�
	int time[],              // ������?��
	int& power               // ���@�̃p?�[
	                         // �i�o���l�C�Ӽ��{���Ȃǁj
) {
	// �S�Ă̒e�ɂ���??���s��
	for (int i=0; i<num_bullet; i++) {

		// �ʏ���ԁF
		// ?���蔻�]??���s���C�e�m���@�ɂ���������C
		// ��������Ԃɂ���B
		// ��������Ԃ̎c��?�Ԃ�݃]���C���@�̃p?�[��?�₷�B
		if (!grazing[i]) {
			if (gx0<x1[i] && x0[i]<gx1 && 
				gy0<y1[i] && y0[i]<gy1) {
				grazing[i]=true;
				time[i]=20;
				power++;
			}
		}
		
		// ��������ԁF
		// ��������Ԃ̎c��?�Ԃ����炵�C
		// ?�Ըm0�ɂȂ�����ʏ���Ԃɖ߂�B
		// ����??���Ȃ����΁C1�̒e��1�g����������Ȃ��Ȃ�B
		else {
			if (time[i]==0) grazing[i]=false; else time[i]--;
		}
	}
	
}
