#include <stdlib.h>

// “G‚Ìî•ñi\‘¢‘Ìj
typedef struct ENEMY_STRUCT {
	float X, Y;                 // Œ»Ý‚ÌÀ•W
	float OldX[INTERVAL];       // ŒÃ‚¢XÀ•W
	float OldY[INTERVAL];       // ŒÃ‚¢YÀ•W
	int Index;                  // Å‚àŒÃ‚¢À•W‚ðŽw‚·ƒC?ƒfªóƒNƒX
	struct ENEMY_STRUCT* Prec;  // 1‚Â‘O‚Ì“G
} ENEMY;

// ŒtÇì‚Ì¶¬
void eFormation(
	float x, float y,  // ¶¬’n¼¨‚ÌÀ•W
	int count          // ŒtÇì‚ð\¬‚·‚é“G‚Ì?
) {
	ENEMY* enemy;      // “G‚ð•\‚·\‘¢‘Ì‚Ö‚Ìƒ|ƒC?ƒ^
	ENEMY* prec=NULL;  // 1‚Â‘O‚Ì“G‚ðŽw‚·ƒ|ƒC?ƒ^
	
	// ŒtÇì‚ð\¬‚·‚é“G‚ðì‚éF
	// “G‚Ì\‘¢‘Ì‚ðŠmÊ÷‚µCÀ•W‚ð?Šú‰»‚·‚éB
	// \‘¢‘ÌŠmÊ÷‚Ì‹ï‘Ì“I‚È??‚ÍNewEnemyTypeŠÖ?‚Ås´Ó‚Æ‚·‚éB
	for (int i=0; i<count; i++, prec=enemy) {
		enemy=NewEnemyType();
		enemy->X=x;
		enemy->Y=y;
		for (int j=0; j<INTERVAL; j++) {
			enemy->OldX[j]=x;
			enemy->OldY[j]=y;
		}
		enemy->Index=0;

		// æˆüˆÈŠO‚Ì“G‚Í1‚Â‘O‚Ì“G‚ðŽQÆ‚µC
		// æ’[‚Ì“G‚ÍNULL‚ðŽQÆ‚·‚éB
		enemy->Prec=prec;
	}
}

