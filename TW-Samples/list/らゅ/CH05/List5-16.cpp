#include <math.h>

void DeleteBullet(int id);
void Shot(float x, float y, float vx, float vy);

void ReflectBullet(
	float fx0, float fy0,    // �t�B�[?�h�̍�����W
	float fx1, float fy1,    // �t�B�[?�h�̅������W
	int num_bullet,          // �e��?
	float x0[], float y0[],  // �e�̍�����W
	float x1[], float y1[],  // �e�̅������W
	float x[], float y[],    // �e��?�S���W
	float ex[], float ey[],  // �e��?�����G��?�S���W
	float speed              // �V?��g�̑���
) {
	// �S�Ă̒e�Ɋւ���??���s��
	for (int i=0; i<num_bullet; i++) {
	
		// �e�ƃt�B�[?�h�Ƃ�?���蔻�]??�F
		// �e�m�t�B�[?�h�ɐڐG������C
		// �e�������āC�����ʒu����G���؂����ăV?��g��?�B
		if (fx0<x1[i] && x0[i]<fx1 && 
			fy0<y1[i] && y0[i]<fy1) {

			// �e�̏�?�F
			// ��̓I��??��DeleteBullet��?�ōs�ӂƂ���B
			DeleteBullet(i);
			
			// �V?��g�̔��ˁF
			// �G���؂����ăV?��g��?�B
			// ���˂̋�̓I��??��Shot��?�ōs�ӂƂ���B
			float vx=ex[i]-x[i], vy=ey[i]-y[i];
			if (vx!=0 || vy!=0) {
				float d=sqrt(vx*vx+vy*vy);
				vx*=speed/d;
				vy*=speed/d;
				Shot(x[i], y[i], vx, vy);
			}
		}
	}
}
