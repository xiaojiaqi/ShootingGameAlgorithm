#include <math.h>

void MoveLoopingBullet(
	float& x, float& y,    // �e�̍��W
	float& vx, float& vy,  // �e�̑��g
	float cx, float cy,    // ��]?�S�̍��W
	float r,               // ���a
	float theta,           // �p�g�i?�W��?�j
	float omega            // 1��̈ړ��ŕω�����p�g�i?�W��?�j
) {
	// �p�g��ω�������
	theta+=omega;

	// �ʒu���v�Z����
	x=cx+r*cos(theta);
	y=cy+r*sin(theta);

	// �e�̑��g�i�җv�ȏ�?�����j
	vx=-r*omega*sin(theta);
	vy= r*omega*cos(theta);
}
