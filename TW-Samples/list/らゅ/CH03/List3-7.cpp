void Warp(
	float& x, float& y,    // Ž©‹@‚ÌÀ•W
	float speed,           // Ž©‹@‚ÌˆÚ“®‘¬Ãg
	float warp_dist,       // ?[ƒv‚ÌˆÚ“®?—£
	bool up, bool down,    // ƒXƒeƒBªóƒN“ü—Íiã‰ºj
	bool left, bool right  // ƒXƒeƒBªóƒN“ü—Íi¶…¸j
) {
	static bool 
		up0=false, down0=false,     // ‘O‰ñ‚ÌƒXƒeƒBªóƒN“ü—Í
		left0=false, right0=false,  // iã‰ºC¶…¸j
		released=true;              // –³“ü—ÍóÆÔ‚É‚µ‚½‚©‚Ç´Ó‚©
	static int time=0;              // “ü—Í‚Ì§ŒÀ?ŠÔ

	// ƒXƒeƒBªóƒN¸m“ü—Í‚³‚ê‚½‚Æª½
	if (up || down || left || right) {
		
		// ?[ƒv‚·‚éê?F
		// –³“ü—Í‚ð‚Í‚³‚ñ‚ÅC‚©‚Â§ŒÀ?ŠÔ…¯‚ÉC
		// ‘O‰ñ‚Æ“¯‚¶•ûÅØ¸m“ü—Í‚³‚ê‚½‚Æª½B
		if (released && time>0 &&
			up==up0 && down==down0 &&
			left==left0 && right==right0
		) {
			if (up   ) y-=warp_dist;
			if (down ) y+=warp_dist;
			if (left ) x-=warp_dist;
			if (right) x+=warp_dist;
		}
		
		// ?[ƒv‚µ‚È‚¢ê?F
		// –³“ü—Í‚ð‚Í‚³‚ñ‚Å‚¢‚È‚¢‚©C§ŒÀ?ŠÔØ‚ê‚©C
		// ‘O‰ñ‚ÆˆÙ‚È‚é•ûÅØ¸m“ü—Í‚³‚ê‚½‚Æª½B
		// •ûÅØ‚ð‹L˜^‚µC§ŒÀ?ŠÔ‚ðÝƒ]‚·‚éB
		else {
			up0=up; down0=down;
			left0=left; right0=right;
			time=10;
			
			// ?’Ê‚ÉˆÚ“®‚·‚é
			if (up   ) y-=speed;
			if (down ) y+=speed;
			if (left ) x-=speed;
			if (right) x+=speed;
		}

		released=false;
	}
	
	// ƒXƒeƒBªóƒN¸m–³“ü—ÍóÆÔ‚Ì‚Æª½
	else released=true;
	
	// ?ŠÔ‚ðŒ¸‚ç‚·
	if (time>0) time--;
}

