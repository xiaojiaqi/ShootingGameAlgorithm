void Barrier1(
	float x0, float y0,        // ƒo?¥Â‚Ì?‚½‚è”»ƒ]
	float x1, float y1,        // i¶ãÀ•WC…¸‰ºÀ•Wj
	float bx0[], float by0[],  // ’e‚Ì?‚½‚è”»ƒ]
	float bx1[], float by1[],  // i¶ãÀ•WC…¸‰ºÀ•Wj
	int num_bullet,            // ’e‚Ì?
	float ex0[], float ey0[],  // “G‚Ì?‚½‚è”»ƒ]
	float ex1[], float ey1[],  // i¶ãÀ•WC…¸‰ºÀ•Wj
	int num_enemy,             // “G‚Ì?
	int& damage,               // ƒo?¥Â‚É¶ÔÏ‚³‚ê‚½ƒ_?[ƒW
	int max_damage             // ƒo?¥Â‚Ìƒ_?[ƒW‚ÌŒÀŠE’l
) {
	// ƒo?¥Â‚Æ’e‚Æ‚Ì?‚½‚è”»ƒ]??F
	// ’e¸m?‚½‚Á‚½‚çC’e‚ðÁ‚µCƒo?¥Â‚Ìƒ_?[ƒW‚ð?‚â‚·B
	// ’e‚ðÁ‚·‹ï‘Ì“I‚È??‚ÍDeleteBulletŠÖ?‚Ås´Ó‚Æ‚·‚éB
	for (int i=0; i<num_bullet && damage<max_damage; i++) {
		if (bx0[i]<x1 && x0<bx1[i] && 
			by0[i]<y1 && y0<by1[i]) {
			DeleteBullet(i);
			damage++;
		}
	}

	// ƒo?¥Â‚Æ“G‚Æ‚Ì?‚½‚è”»ƒ]??F
	// “G¸m?‚½‚Á‚½‚çC“G‚Éƒ_?[ƒW‚ð—^·VC
	// ƒo?¥Â‚Ìƒ_?[ƒW‚à?‚â‚·B
	// “G‚Éƒ_?[ƒW‚ð—^·V‚é‹ï‘Ì“I‚È??‚ÍC
	// DamageEnemyŠÖ?‚Ås´Ó‚Æ‚·‚éB
	for (int i=0; i<num_enemy && damage<max_damage; i++) {
		if (ex0[i]<x1 && x0<ex1[i] && 
			ey0[i]<y1 && y0<ey1[i]) {
			DamageEnemy(i);
			damage++;
		}
	}
	
	// ƒ_?[ƒW¸mŒÀŠE’l‚ð’´·V‚½‚Æª½F
	// ƒo?¥Â‚ðÁ–Å‚³‚¹‚éB
	// Á–Å‚Ì‹ï‘Ì“I‚È??‚ÍDeleteBarrierŠÖ?‚Ås´Ó‚Æ‚·‚éB
	if (damage>=max_damage) DeleteBarrier();
}
