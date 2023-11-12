#include <math.h>

void Shot(float x, float y, float vx, float vy);

void MoveSight2(
	float& x, float& y,       // ���@�̍��W
	float speed,              // ���@�̑���
	bool up1, bool down1,     // ���@�p�X�e�B��N����1�i�㉺�j
	bool left1, bool right1,  // ���@�p�X�e�B��N����1�i�����j
	float& sx, float& sy,     // ��?�̍��W
	float sight_speed,        // ��?�̑���
	bool up2, bool down2,     // ��?�p�X�e�B��N����2�i�㉺�j
	bool left2, bool right2,  // ��?�p�X�e�B��N����2�i�����j
	bool button,              // �V?��g�{�^?�̓���
	float shot_speed          // �V?��g�̑���
) {
	// ���@�𓮂���
	if (up1   ) y-=speed;
	if (down1 ) y+=speed;
	if (left1 ) x-=speed;
	if (right1) x+=speed;

	// ��?�𓮂���
	if (up2   ) sy-=sight_speed;
	if (down2 ) sy+=sight_speed;
	if (left2 ) sx-=sight_speed;
	if (right2) sx+=sight_speed;

	// �V?��g��?�F
	// �V?��g�{�^?�m?���ꂽ��C
	// ���@�����?���؂����ăV?��g��?�B
	// ���˂̋�̓I��??��Shot��?�ōs�ӂƂ���B
	if (button) {
		float vx=sx-x, vy=sy-y;
		if (vx!=0 || vy!=0) {
			float d=sqrt(vx*vx+vy*vy);
			vx*=shot_speed/d;
			vy*=shot_speed/d;
			Shot(x, y, vx, vy);
		}
	}
}

