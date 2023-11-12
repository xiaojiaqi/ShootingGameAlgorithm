#include <math.h>

void SpecialShot(float x, float y, float vx, float vy);

void ReinforcedShot2(
	float x, float y,    // ���@�̍��W
	float cx, float cy,  // �����@�̍��W
	float speed          // �V?��g�̑���
) {
	// �V?��g�̑��g��?�߂�
	float vx=x-cx, vy=y-cy;
	float d=sqrt(vx*vx+vy*vy);
	vx*=speed/d;
	vy*=speed/d;

	// �V?��g�𔭎˂���F
	// ���˂̋�̓I��??��SpecialShot��?�ōs�ӂƂ���B
	SpecialShot(x, y, vx, vy);
}

