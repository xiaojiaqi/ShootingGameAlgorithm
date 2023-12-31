#include "Hit.h"


// 当たり判定が重なっていたらtrueを返す
bool CHit::IsHit(float x, float y, CHit& op, float ox, float oy) {
	float
		l=x+L, t=y+T, 
		r=x+R, b=y+B,
		opl=ox+op.L, opt=oy+op.T, 
		opr=ox+op.R, opb=oy+op.B;
	if (l==r || t==b || opl==opr || opt==opb) return false;
	return !(r<=opl || opr<=l || b<=opt || opb<=t);
}


// 当たり判定が完全に内部にあればtrueを返す
bool CHit::IsInside(float x, float y, CHit& op, float ox, float oy) {
	float
		l=x+L, t=y+T, 
		r=x+R, b=y+B,
		opl=ox+op.L, opt=oy+op.T, 
		opr=ox+op.R, opb=oy+op.B;
	return (opl<=l && r<=opr && opt<=t && b<=opb);
}



