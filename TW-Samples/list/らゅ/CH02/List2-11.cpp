#include <math.h>

// ���@�̈ʒu���i������e�[�u?
int mpos[360][2];

// �e�[�u?�����F
// M_PI�͉~�����B
void MakeTable() {
	for (int i=0; i<360; i++) {
		mpos[i][0]=cos(M_PI/180*i)*1000;
		mpos[i][1]=sin(M_PI/180*i)*1000;
	}
}
