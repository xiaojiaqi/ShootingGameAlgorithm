void ShotAndLaser(
	bool button,    // ƒ{ƒ^?‚ÌóÆÔi?‚³‚ê‚½‚Æª½truej
	int min_power,  // —­‚ßƒp?[‚ÌÅ¬’l
	int max_gauge   // ˜AËƒQ[ƒW‚ÌÅ‘å’l
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
		// ˜AËƒQ[ƒW‚ğ0‚É‚µ‚ÄC?[ƒU[‚ğ?‚ÂB
		// ‹ï‘Ì“I‚È??‚ÍLaserŠÖ?‚Ås´Ó‚Æ‚·‚éB
		else {
			gauge=0;
			Laser();
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
