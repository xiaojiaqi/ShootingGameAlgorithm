// p?[¥ÂªóvÌíÞ
typedef enum {
	NONE,  // §¼[\?¸mÈ¢óÆÔ
	SPEED, MISSILE, DOUBLE, 
	LASER, OPTION, BARRIER, 
	END    // Q[WÌ¸[ð¦·
} POWER_UP_TYPE;

// Q[WðgÁ½p?[¥Âªóv
void PowerUpGauge(
	bool power_up_button  // p?[¥Âªóv{^?ÌüÍ
) {
	static POWER_UP_TYPE cursor=NONE;  // §¼[\?ÌÊu
	
	// ¥ÂCe?ðEÁ½Æª½Ì??F
	// ¥ÂCe?ðEÁ½çC§¼[\?ð1Â¸É®©·B
	// ¸[ÜÅ®¢½ç¶[Éß·B
	// E¢»]??ÍPickItemÖ?Ås´ÓÆ·éB
	if (PickItem()) {
		cursor++;
		if (cursor==END) cursor=SPEED;
	}
	
	// p?[¥ÂªóvÌ??F
	// {^?¸m?³ê½çC
	// §¼[\?¸mwµÄ¢ép?[¥Âªóvðs´ÓB
	// ïÌIÈ??ÍPowerUpÖ?Ås´ÓÆ·éB
	if (power_up_button) {
		PowerUp(cursor);
	}
}

