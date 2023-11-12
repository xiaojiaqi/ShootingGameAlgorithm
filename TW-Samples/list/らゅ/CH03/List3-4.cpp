void Draw(int roll);

void RollMyShip3D(
	int& roll,             // ?[?‚ÌŠpÃg
	bool left, bool right  // ¶…¸•ûÅØ‚Ö‚ÌƒXƒeƒBªóƒN“ü—Í
) {
	// ƒXƒeƒBªóƒN‚Å¶‚ð“ü—Í‚µ‚½ê?F
	// -60<roll‚È‚ç‚Îroll‚ð-3‚·‚éB
	if (left && -60<roll) roll-=3;

	// ƒXƒeƒBªóƒN‚Å…¸‚ð“ü—Í‚µ‚½ê?F
	// roll<60‚È‚ç‚Îroll‚ð+3‚·‚éB
	if (right && roll<60) roll+=3;

	// ƒXƒeƒBªóƒN‚Å¶‚à…¸‚à“ü—Í‚µ‚Ä‚¢‚È‚¢ê?F
	// roll¸m0‚É‹ß‚Ã‚­‚æ´Ó‚É‚·‚éB
	if (!left && !right) {
		if (roll<0) roll+=3; else
		if (0<roll) roll-=3;
	}

	// roll‚Ì’l‚É?‚¶‚ÄŽ©‹@‚ð‰ñ“]‚³‚¹‚Ä•\Ž¦‚·‚éF
	// •\Ž¦‚Ì‹ï‘Ì“I‚È??‚ÍDrawŠÖ?‚Ås´Ó‚Æ‚·‚éB
	Draw(roll);
}