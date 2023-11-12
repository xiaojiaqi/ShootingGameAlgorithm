#include <math.h>

void InitNWayBullets(
	float vx0, float vy0,    // ?S‚Æ‚È‚é’e‚Ì‘¬Ãg
	float theta,             // ’e‚Æ’e‚ÌŠÔ‚ÌŠpÃg
	int n,                   // ’e‚Ì?
	float vx[], float vy[]   // n-way’e‚Ì‘¬Ãg
) {
	// ’e‚Æ’e‚ÌŠÔ‚ÌŠpÃg‚ğ?ƒW¥Â?‚É•ÏŠ·‚·‚é
	float rad_step=M_PI/180*theta;
	
	// ’[‚Ì’e‚Æ?S‚Ì’e‚Æ‚ÌŠÔ‚ÌŠpÃg‚ğŒvZ‚·‚é
	float rad=n%2 ? -n/2*rad_step : (-n/2+0.5)*rad_step;

	// nŒÂ‚Ì’e‚Ì‘¬Ãg‚ğŒvZ‚·‚é
	for (int i=0; i<n; i++, rad+=rad_step) {
		
		// (vx[i],vy[i])‚ğ?‚ß‚éF
		// ‘¬ÃgƒxƒNƒg?(vx0,vy0)‚ğrad‚¾‚¯‰ñ“]‚³‚¹‚éB
		float c=cos(rad), s=sin(rad);
		vx[i]=vx0*c-vy0*s;
		vy[i]=vx0*s+vy0*c;
	}
}
