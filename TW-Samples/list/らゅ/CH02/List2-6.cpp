void MoveAimingBulletFP(
	int& x, int& y,  // ’e‚ÌÀ•W
	int vx, int vy   // ’e‚Ì‘¬Ãg
) {
	// ’e‚ÌÀ•W(x,y)‚É‘¬Ãg(vx,vy)‚ð‰Á·V‚é
	x+=vx;
	y+=vy;

	// ’e‚ð•`‚­F
	// ‰æ–Ê‚É’e‚ð•`‚­‚Æª½‚É‚ÍÀ•W‚ð(x>>8, y>>8)‚Æ‚·‚éB
	// ’e‚ð•`‚­‹ï‘Ì“I‚È??‚ÍDrawŠÖ?‚Ås´Ó‚Æ‚·‚éB
	Draw(x>>8, y>>8);
}