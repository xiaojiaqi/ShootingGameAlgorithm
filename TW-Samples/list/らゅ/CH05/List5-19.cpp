void Slowing(
	int& gauge,  // �X?�[���Ԃɂ��邽�߂ɱҗv�ȃQ�[�W
	bool button  // �X?�[�{�^?��?���Ă��邩�Ǵӂ�
) {
	// �^�C�}�[�F
	// �X?�[���Ԃ̂ƪ��ɍs����?�𒲐����邽�߂Ɏg�ӁB
	static int time=1;

	// �G�ƒe�𓮂����F
	// �ʏ���Ԃ̂ƪ��ɂ�?�񓮂����C
	// �X?�[���Ԃ̂ƪ��ɂ�2���1�񂾂��������B
	// �ړ��̋�̓I��??�́C
	// MoveEnemy�CMoveBullet�̊e��?�ōs�ӂƂ���B
	if (!button || (gauge>0 && time==0)) {
		MoveEnemy();
		MoveBullet();
	}
	
	// �y�i?�e�B�F
	// �Q�[�W�m0�Ȃ̂ɃX?�[�{�^?��?���Ă�����C
	// �y�i?�e�B�Ƃ��Ēe�����1�g�������B
	// ?�ʂƂ��āC�e�͒ʏ��2�{�̑��g�œ����B
	if (button && gauge==0) {
		MoveBullet();
	}

	// �^�C�}�[�̍X��
	if (time>0) time--; else time=1;
}

