#include <math.h>

void InitAimingBullet(
	float mx, float my,   // ���@�̍��W
	float ex, float ey,   // �G�̍��W
	float speed,          // �e�̑���
	float& x, float& y,   // �e�̍��W
	float& vx, float& vy  // �e�̑��g
) {
	// �e�̍��W��݃]����
	x=ex; y=ey;

	// �ڕW�܂ł�?��d��?�߂�
	float d=sqrt((mx-ex)*(mx-ex)+(my-ey)*(my-ey));

	// �����m��]�lspeed�ɂȂ��ӂɑ��g(vx,vy)��?�߂�F
	// �ڕW�܂ł�?��d�m0�̂ƪ��ɂ͉����؂ɔ��˂���B
	if (d) {
		vx=(mx-ex)/d*speed;
		vy=(my-ey)/d*speed;
	} else {
		vx=0;
		vy=speed;
	}
}