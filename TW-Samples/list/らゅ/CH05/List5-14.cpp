void ReinforcedShot3(
	float sx0, float sy0,  // �V?��g�̍�����W
	float sx1, float sy1,  // �V?��g�̅������W
	float cx0, float cy0,  // �����̍�����W
	float cx1, float cy1   // �����̅������W
) {
	// �V?��g�Ɩ����Ƃ�?���蔻�]??�F
	// ?�������ƪ��ɂ̓V?��g�������C
	// ����ɂp���V?��g���o���B
	// ��̓I��??�́C
	// DeleteShot�CSpecialShot�̊e��?�ōs�ӂƂ���B
	// �V?��g���������ɁC
	// �V?��g�̂p��������ϷV����@��?��B
	if (cx0<sx1 && sx0<cx1 && cy0<sy1 && sy0<cy1) {
		DeleteShot();
		SpecialShot();
	}
}

