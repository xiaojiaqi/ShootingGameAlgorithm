void Shot();

void BasicShot(
	bool button  // ����̃{�^?�̏��ԁi?���ꂽ�ƪ�true�j
) {
	// �O��̃{�^?�̏��ԁi?���ꂽ�ƪ�true�j
	static bool prev_button=false;
	
	// �V?��g�̔��ˁF
	// �O��{�^?�m?����įu�炸�C����?����Ă���ƪ������C
	// �V?��g�𔭎˂���B
	// ���˂̏ڍׂ�??��Shot��?�ōs�ӂ��̂Ƃ���B
	if (!prev_button && button) Shot();
	
	// ����̃{�^?�̏��Ԃ���������
	prev_button=button;
}
