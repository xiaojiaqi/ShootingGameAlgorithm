void InitDirectedBullet(
	float ex, float ey,    // “G‚ÌÀ•W
	float& x, float& y,    // ’e‚ÌÀ•W
	float& vx, float& vy,  // ’e‚Ì‘¬Ãg
	float speed,           // ’e‚Ì‘¬‚³
	float theta            // ”­ËŠpÃg
) {
	// ’e‚ÌÀ•W‚ğİƒ]‚·‚é
	x=ex; y=ey;

	// ‘¬‚³speed‚ÅŠpÃgtheta‚Ì•ûÅØ‚É”ò‚Ô’e‚Ì‘¬Ãg(vx,vy)‚ğ?‚ß‚éF
	// M_PI‚Í‰~ü—¦B
	vx=cos(M_PI/180*theta)*speed;
	vy=sin(M_PI/180*theta)*speed;
}