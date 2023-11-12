void CapturedEnemy(
	float& x0, float& y0,      // –¡•û‚É‚È‚Á‚½“G‚Ì¶ãÀ•W
	float& x1, float& y1,      // –¡•û‚É‚È‚Á‚½“G‚Ì…¸‰ºÀ•W
	float ex0[], float ey0[],  // ‘¼‚Ì“G‚Ì¶ãÀ•W
	float ex1[], float ey1[],  // ‘¼‚Ì“G‚Ì…¸‰ºÀ•W
	int num_enemy,             // ‘¼‚Ì“G‚Ì?
	float bx0[], float by0[],  // ’e‚Ì¶ãÀ•W
	float bx1[], float by1[],  // ’e‚Ì…¸‰ºÀ•W
	int num_bullet,            // ’e‚Ì?
	bool button                // ƒV?ªóƒgƒ{ƒ^?‚ÌóÆÔ
) {
	static int damage;         // Œ»Ý‚Ìƒ_?[ƒW
	static int max_damage=40;  // ƒ_?[ƒW‚ÌŒÀŠE’l

	// “G‚Æ‚Ì?‚½‚è”»ƒ]??F
	// “G‚ÆÕªw‚µ‚½‚çC“G‚Éƒ_?[ƒW‚ð—^·VC
	// Ž©•ª‚àƒ_?[ƒW‚ðŽó‚¯‚éB
	// ƒ_?[ƒW•t—^‚Ì‹ï‘Ì“I‚È??‚ÍC
	// DamageEnemyŠÖ?‚Ås´Ó‚Æ‚·‚éB
	for (int i=0; i<num_enemy; i++) {
		if (ex0[i]<x1 && x0<ex1[i] && 
			ey0[i]<y1 && y0<ey1[i]) {
			DamageEnemy(i);
			damage++;
		}
	}
	
	// ’e‚Æ‚Ì?‚½‚è”»ƒ]??F
	// ’e‚ÆÕªw‚µ‚½‚çC’e‚ðÁ‚µC
	// Ž©•ª‚àƒ_?[ƒW‚ðŽó‚¯‚éB
	// Á?‚Ì‹ï‘Ì“I‚È??‚ÍC
	// DeleteBulletŠÖ?‚Ås´Ó‚Æ‚·‚éB
	for (int i=0; i<num_bullet; i++) {
		if (bx0[i]<x1 && x0<bx1[i] && 
			by0[i]<y1 && y0<by1[i]) {
			DeleteBullet(i);
			damage++;
		}
	}
	
	// ?ŒìŽË?F
	// Ž©‹@‚ÌƒV?ªóƒg?ì‚É?‚í‚¹‚ÄƒV?ªóƒg‚ð?‚ÂB
	// ”­ŽË‚Ì‹ï‘Ì“I‚È??‚ÍShotŠÖ?‚Ås´Ó‚Æ‚·‚éB
	if (button) Shot();

	// ƒ_?[ƒW”»ƒ]F
	// ƒ_?[ƒW¸mŒÀŠE’l‚Ü‚Å¶ÔÏ‚µ‚½‚çÁ–Å‚·‚éB
	// Á–Å‚Ì‹ï‘Ì“I‚È??‚ÍC
	// DeleteCapturedEnemyŠÖ?‚Ås´Ó‚Æ‚·‚éB
	if (damage>=max_damage) DeleteCapturedEnemy();
}
