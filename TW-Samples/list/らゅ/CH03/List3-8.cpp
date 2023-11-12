void SpeedControlByButton(
	float& speed,     // �X�s�[�h
	float accel,      // �X�s�[�h�ª�v���g?��
	float max_speed,  // ��?��
	float min_speed,  // �Œᑬ
	bool button       // ���g���߃{�^?�̓���
) {
	// �O��̃{�^?�̏���
	static bool prev_button=false;
	
	// �{�^?�����g������?������?�F
	// ���g���߂��s�ӁB
	if (!prev_button && button) {
		if (speed>=max_speed) speed=min_speed;
		else speed+=accel;
	}
	
	// �{�^?�̏��Ԃ��L�^����
	prev_button=button;
}
