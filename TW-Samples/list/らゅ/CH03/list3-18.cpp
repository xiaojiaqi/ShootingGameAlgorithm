void Barrier2(
	float x0, float y0,        // ƒo?¥Â‚Ì?‚½‚è”»ƒ]
	float x1, float y1,        // i¶ãÀ•WC…¸‰ºÀ•Wj
	float bx0[], float by0[],  // ’e‚Ì?‚½‚è”»ƒ]
	float bx1[], float by1[],  // i¶ãÀ•WC…¸‰ºÀ•Wj
	int num_bullet,            // ’e‚Ì?
	float ex0[], float ey0[],  // “G‚Ì?‚½‚è”»ƒ]
	float ex1[], float ey1[],  // i¶ãÀ•WC…¸‰ºÀ•Wj
	int num_enemy,             // “G‚Ì?
	int& energy,               // ƒo?¥Â‚ÌƒGƒl?ƒM[
	bool barrier_button        // ƒo?¥Âƒ{ƒ^?‚ÌóÆÔ
) {
	// ƒo?¥Â‚ð’£‚éF
	// ƒo?¥Âƒ{ƒ^?¸m?‚³‚ê‚Ä¯u‚èC
	// ‚©‚ÂƒGƒl?ƒM[¸m?‚é‚Æª½‚É‚ÍCƒo?¥Â‚ð’£‚éB
	if (barrier_button && energy>0) {
	
		// ƒo?¥Â‚Æ’e‚Æ‚Ì?‚½‚è”»ƒ]??F
		// ’e¸m?‚½‚Á‚½‚çC’e‚ðÁ‚µCƒo?¥Â‚ÌƒGƒl?ƒM[‚ðŒ¸‚ç‚·B
		// ’e‚ðÁ‚·‹ï‘Ì“I‚È??‚ÍDeleteBulletŠÖ?‚Ås´Ó‚Æ‚·‚éB
		for (int i=0; i<num_bullet && energy>0; i++) {
			if (bx0[i]<x1 && x0<bx1[i] && 
				by0[i]<y1 && y0<by1[i]) {
				DeleteBullet(i);
				energy--;
			}
		}

		// ƒo?¥Â‚Æ“G‚Æ‚Ì?‚½‚è”»ƒ]??F
		// “G¸m?‚½‚Á‚½‚çC“G‚Éƒ_?[ƒW‚ð—^·VC
		// ƒo?¥Â‚ÌƒGƒl?ƒM[‚ðŒ¸‚ç‚·B
		// “G‚Éƒ_?[ƒW‚ð—^·V‚é‹ï‘Ì“I‚È??‚ÍC
		// DamageEnemyŠÖ?‚Ås´Ó‚Æ‚·‚éB
		for (int i=0; i<num_enemy && energy>0; i++) {
			if (ex0[i]<x1 && x0<ex1[i] && 
				ey0[i]<y1 && y0<ey1[i]) {
				DamageEnemy(i);
				energy--;
			}
		}

		// ƒGƒl?ƒM[‚ÌÁ”ï
		energy--;
	}
}


