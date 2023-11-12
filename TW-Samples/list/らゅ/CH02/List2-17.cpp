#include <math.h>

void MoveHomingBullet(
	float& x, float& y,    // ’e‚ÌÀ•W
	float& vx, float& vy,  // ’e‚Ì‘¬Ãg
	float mx, float my,    // Ž©‹@‚ÌÀ•W
	float speed,           // ’e‚Ì‘¬‚³
	float theta            // ù‰ñŠpÃg‚ÌãŒÀ
) {
	// ’e‚ÌŒ³‚Ì‘¬Ãg
	float vx0=vx, vy0=vy;

	// Ž©‹@•ûÅØ‚Ì‘¬ÃgƒxƒNƒg?(vx1,vy1)‚ð?‚ß‚é
	float vx1, vy1;
	float d=sqrt((mx-x)*(mx-x)+(my-y)*(my-y));
	if (d) {
		vx1=(mx-x)/d*speed;
		vy1=(my-y)/d*speed;
	} else {
		vx1=0;
		vy1=speed;
	}

	// …¸‰ñ‚èù‰ñŠpÃgãŒÀ‚Ì‘¬ÃgƒxƒNƒg?(vx2,vy2)‚ð?‚ß‚éF
	// M_PI‚Í‰~Žü—¦B
	float rad=M_PI/180*theta;
	float vx2=cos(rad)*vx0-sin(rad)*vy0;
	float vy2=sin(rad)*vx0+cos(rad)*vy0;

	// Ž©‹@•ûÅØ‚Æù‰ñŠpÃgãŒÀ‚Ì‚Ç‚¿‚ç‚É‹È¸m‚é‚©‚ð?‚ß‚é
	if (vx0*vx1+vy0*vy1<=vx0*vx2+vx0*vy2) {
		
		// Ž©‹@•ûÅØ¸mù‰ñ‰Â”\”ÍÊ¤…¯‚Ìê?F
		// Ž©‹@•ûÅØ‚É‹È¸m‚é
		vx=vx0;
		vy=vy0;

	} else {

		// Ž©‹@•ûÅØ¸mù‰ñ‰Â”\”ÍÊ¤ŠO‚Ìê?F
		// ¶‰ñ‚èù‰ñŠpÃgãŒÀ‚Ì‘¬ÃgƒxƒNƒg?(vx3,vy3)‚ð?‚ß‚é
		float vx3= cos(rad)*vx0+sin(rad)*vy0;
		float vy3=-sin(rad)*vx0+cos(rad)*vy0;
		
		// ’e‚©‚çŽ©‹@‚Ö‚Ì?¤IˆÊ’uƒxƒNƒg?(px,py)‚ð?‚ß‚é
		float px=mx-x, py=my-y;
		
		// …¸‰ñ‚è‚©¶‰ñ‚è‚©‚ð?‚ß‚é
		if (px*vx2+py*vy2<=px*vx3+py*vy3) {

			// …¸‰ñ‚è‚Ìê?
			vx=vx2;
			vy=vy2;

		} else {

			// ¶‰ñ‚è‚Ìê?
			vx=vx3;
			vy=vy3;

		}
	}

	// ’e‚ÌÀ•W(x,y)‚ðXöè‚µ‚ÄC’e‚ðˆÚ“®‚³‚¹‚é
	x+=vx;
	y+=vy;
}

