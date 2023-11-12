#include <math.h>

void MoveHomingBullet(
	float& x, float& y,    // �e�̍��W
	float& vx, float& vy,  // �e�̑��g
	float mx, float my,    // ���@�̍��W
	float speed,           // �e�̑���
	float theta            // ����p�g�̏��
) {
	// �e�̌��̑��g
	float vx0=vx, vy0=vy;

	// ���@���؂̑��g�x�N�g?(vx1,vy1)��?�߂�
	float vx1, vy1;
	float d=sqrt((mx-x)*(mx-x)+(my-y)*(my-y));
	if (d) {
		vx1=(mx-x)/d*speed;
		vy1=(my-y)/d*speed;
	} else {
		vx1=0;
		vy1=speed;
	}

	// ��������p�g����̑��g�x�N�g?(vx2,vy2)��?�߂�F
	// M_PI�͉~�����B
	float rad=M_PI/180*theta;
	float vx2=cos(rad)*vx0-sin(rad)*vy0;
	float vy2=sin(rad)*vx0+cos(rad)*vy0;

	// ���@���؂Ɛ���p�g����̂ǂ���ɋȸm�邩��?�߂�
	if (vx0*vx1+vy0*vy1<=vx0*vx2+vx0*vy2) {
		
		// ���@���ظm����\��ʤ���̏�?�F
		// ���@���؂ɋȸm��
		vx=vx0;
		vy=vy0;

	} else {

		// ���@���ظm����\��ʤ�O�̏�?�F
		// ��������p�g����̑��g�x�N�g?(vx3,vy3)��?�߂�
		float vx3= cos(rad)*vx0+sin(rad)*vy0;
		float vy3=-sin(rad)*vx0+cos(rad)*vy0;
		
		// �e���玩�@�ւ�?�I�ʒu�x�N�g?(px,py)��?�߂�
		float px=mx-x, py=my-y;
		
		// ����肩����肩��?�߂�
		if (px*vx2+py*vy2<=px*vx3+py*vy3) {

			// �����̏�?
			vx=vx2;
			vy=vy2;

		} else {

			// �����̏�?
			vx=vx3;
			vy=vy3;

		}
	}

	// �e�̍��W(x,y)���X�肵�āC�e���ړ�������
	x+=vx;
	y+=vy;
}

