void Draw(int x, int y);

void InitAimingBulletFP(
	int mx, int my,    // Ž©‹@‚ÌÀ•W
	int ex, int ey,    // “G‚ÌÀ•W
	int& x, int& y,    // ’e‚ÌÀ•W
	int& vx, int& vy,  // ’e‚Ì‘¬Ãg
	int speed          // ’e‚Ì‘¬‚³
) {
	// ’e‚ÌÀ•W‚ðÝƒ]‚·‚é
	x=ex; y=ey;

	// –Ú•W‚É¤I‚·‚éX•ûÅØ‚ÆY•ûÅØ‚ÌËû•ª‚Ìâ¤I’l(dx,dy)‚ð?‚ß‚é
	int dx=mx>=ex?mx-ex:ex-mx;
	int dy=my>=ey?my-ey:ey-my;

	// X•ûÅØ‚ÆY•ûÅØ‚ÌËû•ª‚Ì´Ó‚¿’·‚¢•û‚ð?—£d‚Æ‚·‚é
	int d=dx>=dy?dx:dy;

	// ‘¬Ãg(vx,vy)‚ð?‚ß‚é
	vx=(mx-ex)*speed/d;
	vy=(my-ey)*speed/d;
}