void LockShot(
	bool button,     // ƒ{ƒ^?‚ÌóÆÔi?‚³‚ê‚½‚Æª½truej
	int min_power,   // —­‚ßƒp?[‚ÌÅ¬’l
	int max_gauge,   // ˜AËƒQ[ƒW‚ÌÅ‘å’l
	int enemy_id,    // ?ªóƒNƒV?ªóƒg¸m’Ç”ö‚µ‚Ä‚¢‚é“G‚ÌID
	                 // i’Ç”ö‚µ‚Ä‚¢‚È‚¢‚Æª½‚É‚Í?‚Ì’lj
	float front_dir  // ©‹@‚Ì³–Ê‚É??‚·‚é•ûÅØ
) {
	// —­‚ßƒp?[C˜AËƒQ[ƒW
	static int power=0, gauge=0;

	// ƒ{ƒ^?‚ğ?‚µ‚Ä‚¢‚éê?
	if (button) {
		
		// —­‚ßƒp?[•s‘«‚Ìê?F
		// —­‚ßƒp?[‚ğ?‚â‚µC˜AËƒQ[ƒW‚ğÅ‘å‚É‚µ‚ÄC
		// ’e‚ğ?‚ÂB‹ï‘Ì“I‚È??‚ÍShotŠÖ?‚Ås´Ó‚Æ‚·‚éB
		if (power<min_power) {
			power++;
			gauge=max_gauge;
			Shot();
		}
	
		// —­‚ßƒp?[íÏ•ª‚Ìê?F
		// ˜AËƒQ[ƒW‚ğ0‚É‚µ‚ÄC?ªóƒNƒV?ªóƒg‚ğ?‚ÂB
		else {
			gauge=0;
			
			// ?ªóƒNƒV?ªóƒg‚ğ?‚ÂF
			// “G‚ğ’Ç”ö‚µ‚Ä‚¢‚é‚Æª½‚Í“G‚ğ‘_‚¢?‚¿‚·‚éB
			// iu©‹@‚ÉÅØ‚©‚Á‚Ä”ò‚Ô’ev‚Æ“¯—lj
			// “G‚ğ’Ç”ö‚µ‚Ä‚¢‚È‚¢‚Æª½‚Í©‹@‚Ì³–Ê‚É’e‚ğ?‚ÂB
			// iu©—R‚È•ûÅØ‚É”ò‚Ô’ev‚Æ“¯—lj
			// ‚»‚ê‚¼‚ê‹ï‘Ì“I‚È??‚ÍAimingShotŠÖ?‚Æ
			// DirectedShotŠÖ?‚Ås´Ó‚Æ‚·‚éB
			if (enemy_id>=0) {
				AimingShot(enemy_id);
			} else {
				DirectedShot(front_dir);
			}
		}
	}
	
	// ƒ{ƒ^?‚ğ—£‚µ‚Ä‚¢‚éê?F
	else {
		
		// ˜AËƒQ[ƒW>0‚Ìê?F
		// ?’Ê‚Ì’e‚ğ?‚¿C˜AËƒQ[ƒW‚ğ-1‚·‚éB
		if (gauge>0) {
			Shot();
			gauge--;
		}

		// —­‚ßƒp?[‚ğ0‚É‚·‚é
		power=0;
	}
}
