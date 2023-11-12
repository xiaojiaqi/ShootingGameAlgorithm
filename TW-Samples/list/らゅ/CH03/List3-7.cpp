void Warp(
	float& x, float& y,    // ���@�̍��W
	float speed,           // ���@�̈ړ����g
	float warp_dist,       // ?�[�v�̈ړ�?��
	bool up, bool down,    // �X�e�B��N���́i�㉺�j
	bool left, bool right  // �X�e�B��N���́i�����j
) {
	static bool 
		up0=false, down0=false,     // �O��̃X�e�B��N����
		left0=false, right0=false,  // �i�㉺�C�����j
		released=true;              // �����͏��Ԃɂ������Ǵӂ�
	static int time=0;              // ���͂̐���?��

	// �X�e�B��N�m���͂��ꂽ�ƪ�
	if (up || down || left || right) {
		
		// ?�[�v�����?�F
		// �����͂��͂���ŁC������?�ԅ��ɁC
		// �O��Ɠ������ظm���͂��ꂽ�ƪ��B
		if (released && time>0 &&
			up==up0 && down==down0 &&
			left==left0 && right==right0
		) {
			if (up   ) y-=warp_dist;
			if (down ) y+=warp_dist;
			if (left ) x-=warp_dist;
			if (right) x+=warp_dist;
		}
		
		// ?�[�v���Ȃ���?�F
		// �����͂��͂���ł��Ȃ����C����?�Ԑ؂ꂩ�C
		// �O��ƈقȂ���ظm���͂��ꂽ�ƪ��B
		// ���؂��L�^���C����?�Ԃ�݃]����B
		else {
			up0=up; down0=down;
			left0=left; right0=right;
			time=10;
			
			// ?�ʂɈړ�����
			if (up   ) y-=speed;
			if (down ) y+=speed;
			if (left ) x-=speed;
			if (right) x+=speed;
		}

		released=false;
	}
	
	// �X�e�B��N�m�����͏��Ԃ̂ƪ�
	else released=true;
	
	// ?�Ԃ����炷
	if (time>0) time--;
}

