#include <math.h>

void InitDirectedBulletDDA(
	int theta,         // 敪幩妏胓
	int ex, int ey,    // 揋偺嵗昗
	int& x, int& y,    // 抏偺嵗昗
	int& vx, int& vy,  // 抏偺堏摦曽咆
	int& dx, int& dy,  // X曽咆偲Y曽咆偺他暘
	int& diff          // 岆他
) {
	// 壖憐揑側帺婡傪?偔偵攝抲偡傞丗
	// M_PI偼墌廃棪丅
	int mx=cos(M_PI/180*theta)*1000;
	int my=sin(M_PI/180*theta)*1000;

	// ?偲偼DDA傪巊偭偨慱偄?偪抏偺??偲摨偠

	// 抏偺嵗昗傪愝僝偡傞
	x=ex; y=ey;

	// 抏偺堏摦曽咆(vx,vy)傪?傔傞丗抣偼1傑偨偼-1
	vx=mx>ex?1:-1;
	vy=my>ey?1:-1;

	// 栚昗偵偡傞X曽咆偲Y曽咆偺他暘偺愨抣(dx,dy)傪?傔傞
	dx=mx>=ex?mx-ex:ex-mx;
	dy=my>=ey?my-ey:ey-my;

	// 岆他diff丗dx>=dy偺偲偼dx/2丆dx<dy偺偲偼dy/2偲偡傞
	diff=dx>=dy?dx/2:dy/2;
}

