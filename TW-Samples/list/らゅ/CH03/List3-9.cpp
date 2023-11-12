void SpeedControlByItem(
	float& speed,          // �X�s�[�h
	float max_speed,       // ��?��
	float min_speed,       // �Œᑬ
	float x0, float y0,    // �E�����]�̍�����W
	float x1, float y1,    // �E�����]�̅������W
	float ix0, float iy0,  // �C�e?��?���蔻�]�̍�����W
	float ix1, float iy1,  // �C�e?��?���蔻�]�̅������W
	float accel            // �X�s�[�h�ª�v�E�_�E?���g?��
) {
	// �C�e?���E�����ƪ���??�F
	// ?���蔻�]??���s���C?�������ƪ��ɂ́C
	// �X�s�[�h�ª�v�܂��̓X�s�[�h�_�E?���s�ӁB
	if (ix0<x1 && x0<ix1 && iy0<y1 && y0<iy1) {
		speed+=accel;
		
		// �ȉ��̂�ӂɂ���ƁC
		// �X�s�[�h�_�E?��1�E���������ŁC
		// �X�s�[�h�m�Œ�ɂȂ��ӂɂŪ���B
		// if (accel<0) speed=min_speed;
		
		// �X�s�[�h�m��?����Œᑬ�𒴷V����␳����
		if (speed>max_speed) speed=max_speed;
		if (speed<min_speed) speed=min_speed;
	}
}
