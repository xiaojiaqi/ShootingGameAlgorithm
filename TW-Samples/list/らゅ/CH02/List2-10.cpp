#include <math.h>

void InitDirectedBulletDDA(
	int theta,         // ���ˊp�g
	int ex, int ey,    // �G�̍��W
	int& x, int& y,    // �e�̍��W
	int& vx, int& vy,  // �e�̈ړ�����
	int& dx, int& dy,  // X���؂�Y���؂�����
	int& diff          // ����
) {
	// ���z�I�Ȏ��@��?���ɔz�u����F
	// M_PI�͉~�����B
	int mx=cos(M_PI/180*theta)*1000;
	int my=sin(M_PI/180*theta)*1000;

	// ?�Ƃ�DDA���g�����_��?���e��??�Ɠ���

	// �e�̍��W��݃]����
	x=ex; y=ey;

	// �e�̈ړ�����(vx,vy)��?�߂�F�l��1�܂���-1
	vx=mx>ex?1:-1;
	vy=my>ey?1:-1;

	// �ڕW�ɤI����X���؂�Y���؂������̐�I�l(dx,dy)��?�߂�
	dx=mx>=ex?mx-ex:ex-mx;
	dy=my>=ey?my-ey:ey-my;

	// ����diff�Fdx>=dy�̂ƪ���dx/2�Cdx<dy�̂ƪ���dy/2�Ƃ���
	diff=dx>=dy?dx/2:dy/2;
}

