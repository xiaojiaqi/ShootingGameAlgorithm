void HitShot(
	float x0, float y0,    // �V?��g��?���蔻�]�̍�����W
	float x1, float y1,    // �V?��g��?���蔻�]�̅������W
	float attack,          // �V?��g�̍U?��
	float ox0, float oy0,  // �I�ۂ�?���蔻�]�̍�����W
	float ox1, float oy1,  // �I�ۂ�?���蔻�]�̅������W
	float endurance,       // �I�ۂ̑ϋv��
	bool invincible        // �I�۸m�j��s�\���Ǵӂ�
) {
	// �V?��g�m�I�ۂ�?��������?
	if (ox0<x1 && x0<ox1 && oy0<y1 && y0<oy1) {

		// �I�۸m���G�łȂ���?�F
		// �V?��g�̍U?�͂ŤI�ۂ̑ϋv�͂����C
		// �ϋv�͸m0�ɂȂ�����I�ۂ������B
		// ��̓I��??��DeleteOpponent��?�ōs�ӂƂ���B
		if (!invincible) {
			endurance-=attack;
			if (endurance<0) DeleteOpponent();
		}
		
		// �V?��g�������F
		// ��̓I��??��DeleteShot��?�ōs�ӂƂ���B
		// �����ŃV?��g�������Ȃ��ƁC�ђʒe�ɂȂ�B
		DeleteShot();
	}
}

