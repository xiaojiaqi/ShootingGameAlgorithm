#include <math.h>

void InitNWayBullets(
	float vx0, float vy0,    // ?�S�ƂȂ�e�̑��g
	float theta,             // �e�ƒe�̊Ԃ̊p�g
	int n,                   // �e��?
	float vx[], float vy[]   // n-way�e�̑��g
) {
	// �e�ƒe�̊Ԃ̊p�g��?�W��?�ɕϊ�����
	float rad_step=M_PI/180*theta;
	
	// �[�̒e��?�S�̒e�Ƃ̊Ԃ̊p�g���v�Z����
	float rad=n%2 ? -n/2*rad_step : (-n/2+0.5)*rad_step;

	// n�̒e�̑��g���v�Z����
	for (int i=0; i<n; i++, rad+=rad_step) {
		
		// (vx[i],vy[i])��?�߂�F
		// ���g�x�N�g?(vx0,vy0)��rad������]������B
		float c=cos(rad), s=sin(rad);
		vx[i]=vx0*c-vy0*s;
		vy[i]=vx0*s+vy0*c;
	}
}
