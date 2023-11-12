void Underwater2(
	float& x, float& y,        // ���@�̍��W
	float x0, float y0,        // ���@�̍�����W
	float x1, float y1,        // ���@�̅������W
	float vx, float vy,        // ���@�̑��g
	float wx0[], float wy0[],  // ?��?���蔻�]
	float wx1[], float wy1[],  // �i������W�C�������W�j
	int num_water              // ?��?���蔻�]��?
) {
	// ���@�m??�ɂ��邩�Ǵӂ��𒲂ׂ�
	int i;
	for (i=0; i<num_water; i++) {
		if (wx0[i]<=x0 && x1<=wx1[i] && 
			wy0[i]<=y0 && y1<=wy1[i]) break;
	}
	
	// ���@�m??�ɂ����?�F
	// ���g����������B�����ł͋�?�̔����Ƃ����B
	if (i<num_water) {
		x+=vx/2; y+=vy/2;
	}
	
	// ���@�m??�ɂ͂��Ȃ���?�F
	// �ʏ�̑��g�ňړ�����
	else {
		x+=vx; y+=vy;
		
		// ���@�m?�ʂɐڐG���Ă��邩�Ǵӂ��𒲂ׂ�
		for (i=0; i<num_water; i++) {
			if (wx0[i]<x1 && x0<wx1[i] && 
				wy0[i]<y1 && y0<wy1[i]) break;
		}

		// ���@�m?�ʂɐڐG���Ă����?�F
		// �g���Ԫ��Ȃǂ̃G�t�F�N�g��\������B
		// ��̓I��??��WaveEffect��?�ōs�ӂƂ���B
		if (i<num_water) WaveEffect();
	}
}

