void MoveGroundMissile(
	float& x0, float& y0,      // ƒ~ƒTƒC?‚Ì¶ãÀ•W
	float& x1, float& y1,      // ƒ~ƒTƒC?‚Ì…¸‰ºÀ•W
	float vx, float vy,        // ƒ~ƒTƒC?‚Ì‘¬Ãgi?•½C?’¼j
	float gx0[], float gy0[],  // ’nŒ`‚Ì¶ãÀ•W
	float gx1[], float gy1[],  // ’nŒ`‚Ì…¸‰ºÀ•W
	int num_ground,            // ’nŒ`‚Ì?
	float ex0[], float ey0[],  // “G‚Ì¶ãÀ•W
	float ex1[], float ey1[],  // “G‚Ì…¸‰ºÀ•W
	int num_enemy              // “G‚Ì?
) {
	// ’nŒ`‚Æ‚Ì?‚½‚è”»ƒ]??F
	// ƒ~ƒTƒC?‚ð?’¼•ûÅØ‚Éi‚ß‚½À•W‚É‚Â‚¢‚ÄC
	// ’nŒ`‚É?‚½‚é‚©‚Ç´Ó‚©‚ð”»ƒ]‚·‚éB
	// ’nŒ`‚É?‚½‚Á‚½ê?‚É‚ÍC?’¼•ûÅØ‚Ì‘¬Ãg‚ð0‚É‚µ‚ÄC
	// ?[ƒv‚©‚ç”²‚¯‚éB
	for (int i=0; i<num_ground; i++) {
		if (gx0[i]<x1 && x0<gx1[i] && 
			gy0[i]<y1+vy && y0+vy<gy1[i]) {
			vy=0;
			break;
		}
	}
	
	// ƒ~ƒTƒC?‚ði‚ß‚é
	x0+=vx; y0+=vy;
	x1+=vx; y1+=vy;

	// “G‚Æ‚Ì?‚½‚è”»ƒ]??F
	// “G‚É?‚½‚Á‚½ê?‚É‚ÍC“G‚Éƒ_?[ƒW‚ð—^·V‚ÄC
	// ?[ƒv‚©‚ç”²‚¯‚éB
	// ƒ_?[ƒW‚Ì‹ï‘Ì“I‚È??‚ÍDamageEnemyŠÖ?‚Ås´Ó‚Æ‚·‚éB
	for (int i=0; i<num_enemy; i++) {
		if (ex0[i]<x1 && x0<ex1[i] && 
			ey0[i]<y1 && y0<ey1[i]) {
			DamageEnemy(i);
			break;
		}
	}
}
