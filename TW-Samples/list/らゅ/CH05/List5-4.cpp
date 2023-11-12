void ItemSpecialAttack(
	float x0, float y0,        // ���@�̍�����W
	float x1, float y1,        // ���@�̅������W
	float ix0[], float iy0[],  // �C�e?�̍�����W
	float ix1[], float iy1[],  // �C�e?�̍�����W
	int num_item               // �C�e?��?
) {
	static bool special=false;  // ���̏��Ըm����Ȃ��true
	static int time;            // ����U?�̎c��?��
	
	// �ʏ���Ԃ̂ƪ�
	if (!special) {

		// �ʏ�U?���s�ӁF
		// ��̓I��??��NormalAttack��?�ōs�ӂƂ���B
		NormalAttack();
		
		// �C�e?���E�������Ǵӂ��̔��]�F
		// �E�����������ԂɈڂ�C�c��?�Ԃ�݃]����B
		for (int i=0; i<num_item; i++) {
			if (ix0[i]<x1 && x0<ix1[i] && 
				iy0[i]<y1 && y0<iy1[i]) {
				special=true;
				time=300;
			}
		}
	}
	
	// ������Ԃ̂ƪ�
	else {
		
		// ����U?���s�ӁF
		// ��̓I��??��SpecialAttack��?�ōs�ӂƂ���B
		SpecialAttack();
		
		// ��]?�Ըm���\�����Ǵӂ��̔��]�F
		// �c��?�Ըm�Ȃ��Ȃ�����ʏ���Ԃɖ߂�B
		if (time==0) special=false; else time--;
	}
}

