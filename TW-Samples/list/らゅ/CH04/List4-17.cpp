// ?���؂�ַV��??
void SelectWeapon(
	bool button  // �{�^?�̏��ԁi?�����ƪ�true�j
) {
	static int weapon_id=0;         // ���ݑI��?��?��̔�?
	static bool prev_button=false;  // �O��̃{�^?�̏���
	
	// ?���؂�ַV��F
	// �O��{�^?��?���įu�炸�C����?���Ă�����C
	// ?��̐؂�ַV���s�ӁB
	if (!prev_button && button) {
		weapon_id=(weapon_id+1)%MAX_WEAPONS;
	}
	
	// ?��̥C�R?��\������F
	// �S�C�R?��\�����C�I��?�̥C�R?�͖ڗ�������B
	// �\���̋�̓I��??��DrawIcon��?��FocusIcon��?��
	// �s�ӂƂ���B
	for (int i=0; i<MAX_WEAPONS; i++) DrawIcon(i);
	FocusIcon(weapon_id);

	// ����̃{�^?�̏��Ԃ���������
	prev_button=button;
}


