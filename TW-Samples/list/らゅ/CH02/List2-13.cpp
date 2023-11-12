#include <math.h>

void RotateVelocity(
	float theta,           // ��]�p�g
	float vx0, float vy0,  // ���̑��g
	float& vx, float& vy   // ��]��̑��g
) {
	// theta��?�W��?�ɕϊ����Ccos��sin��?�߂�F
	// M_PI�͉~�����B
	float rad=M_PI/180*theta;
	float c=cos(rad), s=sin(rad);

	// ���g�x�N�g?(vx0,vy0)����]������(vx,vy)��?�߂�
	vx=vx0*c-vy0*s;
	vy=vx0*s+vy0*c;
}
