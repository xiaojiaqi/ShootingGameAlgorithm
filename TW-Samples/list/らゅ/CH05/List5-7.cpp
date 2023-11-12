void MoveThrownShip(
	float& x0, float& y0,  // ‹@‘Ì‚Ì¶ãÀ•W
	float& x1, float& y1,  // ‹@‘Ì‚Ì…¸‰ºÀ•W
	float& vx, float& vy,  // ‹@‘Ì‚Ì‘¬Ãg
	float sx0, float sy0,  // ˆÚ“®‰Â”\”ÍÊ¤i‰æ–Ê˜gj‚Ì¶ãÀ•W
	float sx1, float sy1   // ˆÚ“®‰Â”\”ÍÊ¤i‰æ–Ê˜gj‚Ì…¸‰ºÀ•W
) {
	// ’µ‚Ë‰ñ‚é“®ª½‚Ì‚½‚ß‚Ì??F
	// ‰æ–Ê˜g‚Ìã‰º¶…¸‚©‚ç‚Í‚Ýo‚µ‚»´Ó‚É‚È‚Á‚½‚çC
	// ˆÚ“®‘¬Ãg‚ðÊä‚É‚·‚éB
	if (x0+vx<sx0 || sx1<=x1+vx) vx=-vx;
	if (y0+vy<sy0 || sy1<=y1+vy) vy=-vy;
	
	// ‹@‘Ì‚ðˆÚ“®‚³‚¹‚é
	x0+=vx; x1+=vx;
	y0+=vy; y1+=vy;
}

