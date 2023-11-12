#ifndef HITH
#define HITH

#include <vector>
using namespace std;


//==============================================================
// 判定是否打中所使用的類別
class CHit {
public:
	float L, R, T, B;

	CHit() : L(0), R(0), T(0), B(0) {}
	CHit(float l, float r, float t, float b)
	:	L(l), R(r), T(t), B(b) {}

	bool IsHit(float x, float y, CHit& op, float ox=0, float oy=0);
	bool IsInside(float x, float y, CHit& op, float ox=0, float oy=0);
	bool IsVoid() { return L==R || T==B; }
	void SetPos(float x, float y) { L+=x; R+=x; T+=y; B+=y; }
};


#endif

