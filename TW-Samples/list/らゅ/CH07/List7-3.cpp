// ¯‚Ìî•ñ‚ğÊ÷?‚·‚é\‘¢‘Ì
typedef struct {
	int X, Y;    // À•W
	int VX, VY;  // ‘¬Ãg
	int Color;     // F
} STAR;

// ¯‚ÌƒXƒN?[?
void DrawStar(
	int num_star,   // ¯‚Ì?
	STAR star[]    // ¯‚Ìî•ñ
) {
	// ¯‚ÌˆÚ“®‚Æ•`‰æF
	// •`‰æ‚Ì‹ï‘Ì“I‚È??‚ÍDrawPixelŠÖ?‚Ås´Ó‚Æ‚·‚éB
	for (int i=0; i<num_star; i++) {
		star[i].X+=star[i].VX;
		star[i].Y+=star[i].VY;
		DrawPixel(star[i].X, star[i].Y, star[i].Color);
	}
}

