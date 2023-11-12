#include <math.h>

void TurnMarker(
	float& x, float& y,     // ���@�̍��W
	float speed,            // ���@�̑���
	bool left, bool right,  // �X�e�B��N�̏��ԁi�������؁j
	bool up, bool down,     // �X�e�B��N�̏��ԁi�㉺���؁j
	bool turn_button,       // ����{�^?�̏���
	bool shot_button        // �V?��g�{�^?�̏���
) {
	static bool turning;        // ����?�Ȃ��true
	static float mx, my;        // �^�[?�}�[���[�̍��W
	static float rad=M_PI*3/2;  // ����p�g�iM_PI�͉~�����j
	static float d=10;          // ���@�ƃ^�[?�}�[���[��?��
	
	// ����̊J�n�F
	// �^�[?�}�[���[�̍��W���Z�o����B
	if (!turning && turn_button) {
		turning=true;
		mx=x-d*cos(rad);
		my=y-d*sin(rad);
	}
	
	// ����̏I��
	if (!turn_button) turning=false;
	
	// ���@�̈ړ�
	if (up   ) y-=speed;
	if (down ) y+=speed;
	if (left ) x-=speed;
	if (right) x+=speed;
	
	// ����?�Ȃ�ΐ���p�g���v�Z����
	if (turning) rad=-atan2(x-mx, y-my);
	
	// �V?��g�̔��ˁF
	// ���@�m�؂��Ă�����؂ɃV?��g��?�B
	// ���˕��؂�rad�Ƃ͔��I���؁i180?=��?�W��?�����j�B
	// ���˂̋�̓I��??��DirectedShot��?�ōs�ӂƂ���B
	if (shot_button) DirectedShot(x, y, rad+M_PI);
}

