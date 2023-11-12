#include <math.h>

void InitCircleBullets(
	int n,                   // �e��?
	float speed,             // �e�̑���
	bool odd,                // ��?�p�^�[?�̂ƪ�true
	float vx[], float vy[]   // �~�`�e�̑��g
) {
	// �e�ƒe�Ƃ̊Ԃ̊p�g���v�Z����
	float rad_step=M_PI*2/n;

	// ��?�̒e�̊p�g���v�Z����F
	// ��?�p�^�[?�̂ƪ��ɂ�rad_step/2�������炷�B
	float rad=odd ? rad_step/2 : 0;

	// n�̒e�̑��g��?�߂�F
	// ����speed�Ŋp�grad�̕��؂ɔ�Ԓe�̑��g��?�߂�B
	// ����͕��ؒe���΂�??��?�p�B
	for (int i=0; i<16; i++, rad+=rad_step) {
		vx[i]=cos(rad)*speed;
		vy[i]=sin(rad)*speed;
	}
}

