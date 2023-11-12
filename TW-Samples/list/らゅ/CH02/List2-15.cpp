#include <math.h>

void InitCircleBullets(
	int n,                   // ’e‚Ì?
	float speed,             // ’e‚Ì‘¬‚³
	bool odd,                // Šï?ƒpƒ^[?‚Ì‚Æª½true
	float vx[], float vy[]   // ‰~Œ`’e‚Ì‘¬Ãg
) {
	// ’e‚Æ’e‚Æ‚ÌŠÔ‚ÌŠpÃg‚ğŒvZ‚·‚é
	float rad_step=M_PI*2/n;

	// Å?‚Ì’e‚ÌŠpÃg‚ğŒvZ‚·‚éF
	// Šï?ƒpƒ^[?‚Ì‚Æª½‚É‚Írad_step/2‚¾‚¯‚¸‚ç‚·B
	float rad=odd ? rad_step/2 : 0;

	// nŒÂ‚Ì’e‚Ì‘¬Ãg‚ğ?‚ß‚éF
	// ‘¬‚³speed‚ÅŠpÃgrad‚Ì•ûÅØ‚É”ò‚Ô’e‚Ì‘¬Ãg‚ğ?‚ß‚éB
	// äø‚ê‚Í•ûÅØ’e‚ğ”ò‚Î‚·??‚Ì?—pB
	for (int i=0; i<16; i++, rad+=rad_step) {
		vx[i]=cos(rad)*speed;
		vy[i]=sin(rad)*speed;
	}
}

