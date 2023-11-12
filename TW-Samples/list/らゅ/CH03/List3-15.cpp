// ƒp?[¥Âªóƒv‚ÌŽí—Þ
typedef enum {
	NONE,  // §¼[ƒ\?¸m‚È‚¢óÆÔ
	SPEED, MISSILE, DOUBLE, 
	LASER, OPTION, BARRIER, 
	END    // ƒQ[ƒW‚Ì…¸’[‚ðŽ¦‚·
} POWER_UP_TYPE;

// ƒQ[ƒW‚ðŽg‚Á‚½ƒp?[¥Âªóƒv
void PowerUpGauge(
	bool power_up_button  // ƒp?[¥Âªóƒvƒ{ƒ^?‚Ì“ü—Í
) {
	static POWER_UP_TYPE cursor=NONE;  // §¼[ƒ\?‚ÌˆÊ’u
	
	// ¥ÂƒCƒe?‚ðE‚Á‚½‚Æª½‚Ì??F
	// ¥ÂƒCƒe?‚ðE‚Á‚½‚çC§¼[ƒ\?‚ð1‚Â…¸‚É“®‚©‚·B
	// …¸’[‚Ü‚Å“®‚¢‚½‚ç¶’[‚É–ß‚·B
	// E‚¢”»ƒ]??‚ÍPickItemŠÖ?‚Ås´Ó‚Æ‚·‚éB
	if (PickItem()) {
		cursor++;
		if (cursor==END) cursor=SPEED;
	}
	
	// ƒp?[¥Âªóƒv‚Ì??F
	// ƒ{ƒ^?¸m?‚³‚ê‚½‚çC
	// §¼[ƒ\?¸mŽw‚µ‚Ä‚¢‚éƒp?[¥Âªóƒv‚ðs´ÓB
	// ‹ï‘Ì“I‚È??‚ÍPowerUpŠÖ?‚Ås´Ó‚Æ‚·‚éB
	if (power_up_button) {
		PowerUp(cursor);
	}
}

