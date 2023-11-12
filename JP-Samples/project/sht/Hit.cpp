#include "Hit.h"


// �����蔻�肪�d�Ȃ��Ă�����true��Ԃ�
bool CHit::IsHit(float x, float y, CHit& op, float ox, float oy) {
	float
		l=x+L, t=y+T, 
		r=x+R, b=y+B,
		opl=ox+op.L, opt=oy+op.T, 
		opr=ox+op.R, opb=oy+op.B;
	if (l==r || t==b || opl==opr || opt==opb) return false;
	return !(r<=opl || opr<=l || b<=opt || opb<=t);
}


// �����蔻�肪���S�ɓ����ɂ����true��Ԃ�
bool CHit::IsInside(float x, float y, CHit& op, float ox, float oy) {
	float
		l=x+L, t=y+T, 
		r=x+R, b=y+B,
		opl=ox+op.L, opt=oy+op.T, 
		opr=ox+op.R, opb=oy+op.B;
	return (opl<=l && r<=opr && opt<=t && b<=opb);
}



