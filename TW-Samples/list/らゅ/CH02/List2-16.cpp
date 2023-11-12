#include <math.h>

void MoveSimpleHomingBullet(
	float& x, float& y,  // �e�̍��W
	float mx, float my,  // ���@�̍��W
	float speed          // �e�̑���
) {
	// �ڕW�܂ł�?��d��?�߂�
	float d=sqrt((mx-x)*(mx-x)+(my-y)*(my-y));

	// �e�̑��g(vx, vy)��?�߂�F
	// �����m��]�lspeed�ɂȂ��ӂɂ���B
	// �ڕW�܂ł�?��d�m0�̂ƪ��ɂ͑��g�������؂ɂ���B
	float vx, vy;
	if (d) {
		vx=(mx-x)/d*speed;
		vy=(my-y)/d*speed;
	} else {
		vx=0;
		vy=speed;
	}

	// �e�̍��W(x,y)���X�肵�āC�e���ړ�������
	x+=vx;
	y+=vy;
}
