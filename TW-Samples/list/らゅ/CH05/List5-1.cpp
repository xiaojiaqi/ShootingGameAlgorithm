void Bomb(
	int& bomb_time,             // ƒ{?‚Ì—LŒø?ŠÔ
	float x0, float y0,        // ƒ{?‚Ì—LŒø”ÍÊ¤‚Ì¶ãÀ•W
	float x1, float y1,        // ƒ{?‚Ì—LŒø”ÍÊ¤‚Ì…¸‰ºÀ•W
	float bx0[], float by0[],  // ’e‚Ì¶ãÀ•W
	float bx1[], float by1[],  // ’e‚Ì…¸‰ºÀ•W
	int num_bullet,            // ’e‚Ì?
	float ex0[], float ey0[],  // “G‚Ì¶ãÀ•W
	float ex1[], float ey1[],  // “G‚Ì…¸‰ºÀ•W
	int num_enemy              // “G‚Ì?
) {
	// ƒ{?¸m—LŒø‚Èê?‚Ì??
	if (bomb_time>0) {
	
		// ’e‚ðÁ‚·F
		// Á?‚Ì‹ï‘Ì“I‚È??‚ÍC
		// DeleteBulletŠÖ?‚Ås´Ó‚Æ‚·‚éB
		for (int i=0; i<num_bullet; i++) {
			if (bx0[i]<x1 && x0<bx1[i] && 
				by0[i]<y1 && y0<by1[i]) {
				DeleteBullet(i);
			}
		}

		// “G‚Éƒ_?[ƒW‚ð—^·V‚éF
		// ƒ_?[ƒW•t—^‚Ì‹ï‘Ì“I‚È??‚ÍC
		// DamageEnemyŠÖ?‚Ås´Ó‚Æ‚·‚éB
		for (int i=0; i<num_enemy; i++) {
			if (ex0[i]<x1 && x0<ex1[i] && 
				ey0[i]<y1 && y0<ey1[i]) {
				DamageEnemy(i);
			}
		}
	
		// ƒ{?‚Ì—LŒø?ŠÔ‚ðŒ¸‚ç‚·
		bomb_time--;
	}
}

