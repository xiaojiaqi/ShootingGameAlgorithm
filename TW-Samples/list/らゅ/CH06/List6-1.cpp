void BreakableEnemy(
	int num_enemy,             // “G‚Ì?
	float ex0[], float ey0[],  // “G‚Ì?‚½‚è”»ƒ]‚Ì¶ãÀ•W
	float ex1[], float ey1[],  // “G‚Ì?‚½‚è”»ƒ]‚Ì…¸‰ºÀ•W
	float vit[],               // “G‚Ì‘Ï‹v—Í
	int num_weapon,            // ?Ší‚Ì?
	float wx0[], float wy0[],  // ?Ší‚Ì?‚½‚è”»ƒ]‚Ì¶ãÀ•W
	float wx1[], float wy1[],  // ?Ší‚Ì?‚½‚è”»ƒ]‚Ì…¸‰ºÀ•W
	float str[]                // ?Ší‚ÌU?—Í
) {
	// “G‚Æ?Ší‚Ì?‚½‚è”»ƒ]??F
	// ‘S‚Ä‚Ì“G‚Æ?Ší‚Ì‘g‚İ?‚í‚¹‚É‚Â‚¢‚ÄC
	// ?Ší¸m“G‚É?‚½‚Á‚½‚©‚Ç´Ó‚©‚ğ”»ƒ]‚·‚é
	for (int i=0; i<num_enemy; i++) {
		for (int j=0; j<num_weapon; j++) {
			if (ex0[i]<wx1[j] && wx0[j]<ex1[i] && 
				ey0[i]<wy1[j] && wy0[j]<ey1[i]
			) {
				// ?‚½‚Á‚½ê?F
				// ?Ší‚ÌU?—Í‚Å“G‚Ì‘Ï‹v—Í‚ğí‚èC
				// ‘Ï‹v—Í¸m0‚Ü‚½‚Í?‚É‚È‚Á‚½‚ç“G‚ğ”j‰ó‚·‚éB
				// ”j‰ó‚Ì‹ï‘Ì“I‚È??‚ÍC
				// DeleteEnemyŠÖ?‚Ås´Ó‚Æ‚·‚éB
				vit[i]-=str[j];
				if (vit[i]<=0) DeleteEnemy(i);
				
				// “G‚É?‚½‚Á‚½?Ší‚ÍÁ‚·F
				// ‹ï‘Ì“I‚È??‚ÍDeleteWeaponŠÖ?‚Ås´Ó‚Æ‚·‚éB
				DeleteWeapon(j);
			}
		}
	}
}

