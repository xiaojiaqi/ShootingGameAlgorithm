//============================================================== (1)
// ƒXƒeƒBªóƒN‚Æƒ{ƒ^?‚ÌóÆÔ‚ð•\‚·ƒ]?F
// 2‚ÂˆÈã‚Ìƒ]?‚ð‘g‚Ý?‚í‚¹‚éäø‚Æ‚à‚Åª½‚éB
// —á·V‚Îu¶ãv‚ÍC
// uãv‚Æu¶v‚Ì‘g‚Ý?‚í‚¹iUP|LEFTj‚Å•\‚·B
#define NONE     0  // ?ŠúóÆÔ
#define NEUTRAL  1  // ƒj?[ƒg??
#define UP       2  // ã
#define DOWN     4  // ‰º
#define LEFT     8  // ¶
#define RIGHT   16  // …¸
#define BUTTON  32  // ƒ{ƒ^?

// “ü—Í?—ð‚ÌŒÂ?C“ü—Í?—ð
#define NUM_HISTORY 30
static int History[NUM_HISTORY];

// ƒRƒ}?ƒh
typedef struct {
	int Length;              // ƒRƒ}?ƒh‚Ì’·‚³
	int Limit;               // “ü—Í?ŠÔ‚Ì§ŒÀ
	int Input[NUM_HISTORY];  // “ü—Í…¯—e
} COMMAND_TYPE;
#define NUM_COMMAND 2
COMMAND_TYPE Command[NUM_COMMAND];

//============================================================== (2)
// “ü—Í?—ð‚ÆƒRƒ}?ƒh‚Ì?Šú‰»
void InitCommandShot()
{
	// “ü—Í?—ð‚Ì?Šú‰»
	for (int i=0; i<NUM_HISTORY; i++) History[i]=NONE;

	// ƒRƒ}?ƒh1i”g“®?ƒRƒ}?ƒhj
	Command[0].Length=4;
	Command[0].Limit=30;
	Command[0].Input[0]=DOWN;
	Command[0].Input[1]=DOWN|RIGHT;
	Command[0].Input[2]=RIGHT;
	Command[0].Input[3]=BUTTON;

	// ƒRƒ}?ƒh2i¸—´?ƒRƒ}?ƒhj
	Command[1].Length=4;
	Command[1].Limit=30;
	Command[1].Input[0]=RIGHT;
	Command[1].Input[1]=DOWN;
	Command[1].Input[2]=DOWN|RIGHT;
	Command[1].Input[3]=BUTTON;
}

//============================================================== (3)
// ƒRƒ}?ƒhƒV?ªóƒg‚Ì”»ƒ]‚ðs´ÓŠÖ?
void CommandShot(
	bool up, bool down,     // ƒXƒeƒBªóƒN‚ÌóÆÔiã‰º¶…¸j
	bool left, bool right,  
	bool button             // ƒ{ƒ^?‚ÌóÆÔi?‚³‚ê‚½‚Æª½truej
) {
	// “ü—Í?—ð‚Ì‹L˜^ˆÊ’u
	static int index=0;
	
	// “ü—Í‚ð?—ð‚É‹L˜^‚·‚é
	History[index]=
		(up?UP:0)|(down?DOWN:0)|
		(left?LEFT:0)|(right?RIGHT:0)|
		(button?BUTTON:0);

	// ŠeƒRƒ}?ƒh¸m“ü—Í‚³‚ê‚½‚©‚Ç´Ó‚©‚ð”»ƒ]‚·‚é
	int c, j, i;
	for (c=0; c<NUM_COMMAND; c++) {
		for (i=0, j=Command[c].Length-1; j>=0; j--) {
			for (; i<Command[c].Limit; i++) {
				if (History[(index-i+NUM_HISTORY)
					%NUM_HISTORY]==Command[c].Input[j]) break;
			}
			if (i==Command[c].Limit) break;
		}
		
		// ƒRƒ}?ƒh‚Ì“ü—Í¸mŠm”F‚Åª½‚½F
		// ƒRƒ}?ƒhƒV?ªóƒg‚ð?‚¿C?—ð‚ðƒN?¥Â‚·‚éB
		// ‹ï‘Ì“I‚È??‚ÍComShotŠÖ?‚Ås´Ó‚Æ‚·‚éB
		if (j==-1) {
			ComShot(j);
			for (i=0; i<NUM_HISTORY; i++) History[i]=NONE;
		}
	}
	
	// ‹L˜^ˆÊ’u‚ðXöè‚·‚é
	index=(index+1)%NUM_HISTORY;
}

