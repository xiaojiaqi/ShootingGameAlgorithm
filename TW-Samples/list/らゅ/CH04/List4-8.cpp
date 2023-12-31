//============================================================== (1)
// XeBªóNÆ{^?ÌóÆÔð\·]?F
// 2ÂÈãÌ]?ðgÝ?í¹éäøÆàÅª½éB
// á·VÎu¶ãvÍC
// uãvÆu¶vÌgÝ?í¹iUP|LEFTjÅ\·B
#define NONE     0  // ?úóÆÔ
#define NEUTRAL  1  // j?[g??
#define UP       2  // ã
#define DOWN     4  // º
#define LEFT     8  // ¶
#define RIGHT   16  // ¸
#define BUTTON  32  // {^?

// üÍ?ðÌÂ?CüÍ?ð
#define NUM_HISTORY 30
static int History[NUM_HISTORY];

// R}?h
typedef struct {
	int Length;              // R}?hÌ·³
	int Limit;               // üÍ?ÔÌ§À
	int Input[NUM_HISTORY];  // üÍ¯e
} COMMAND_TYPE;
#define NUM_COMMAND 2
COMMAND_TYPE Command[NUM_COMMAND];

//============================================================== (2)
// üÍ?ðÆR}?hÌ?ú»
void InitCommandShot()
{
	// üÍ?ðÌ?ú»
	for (int i=0; i<NUM_HISTORY; i++) History[i]=NONE;

	// R}?h1ig®?R}?hj
	Command[0].Length=4;
	Command[0].Limit=30;
	Command[0].Input[0]=DOWN;
	Command[0].Input[1]=DOWN|RIGHT;
	Command[0].Input[2]=RIGHT;
	Command[0].Input[3]=BUTTON;

	// R}?h2i¸´?R}?hj
	Command[1].Length=4;
	Command[1].Limit=30;
	Command[1].Input[0]=RIGHT;
	Command[1].Input[1]=DOWN;
	Command[1].Input[2]=DOWN|RIGHT;
	Command[1].Input[3]=BUTTON;
}

//============================================================== (3)
// R}?hV?ªógÌ»]ðs´ÓÖ?
void CommandShot(
	bool up, bool down,     // XeBªóNÌóÆÔiãº¶¸j
	bool left, bool right,  
	bool button             // {^?ÌóÆÔi?³ê½Æª½truej
) {
	// üÍ?ðÌL^Êu
	static int index=0;
	
	// üÍð?ðÉL^·é
	History[index]=
		(up?UP:0)|(down?DOWN:0)|
		(left?LEFT:0)|(right?RIGHT:0)|
		(button?BUTTON:0);

	// eR}?h¸müÍ³ê½©Ç´Ó©ð»]·é
	int c, j, i;
	for (c=0; c<NUM_COMMAND; c++) {
		for (i=0, j=Command[c].Length-1; j>=0; j--) {
			for (; i<Command[c].Limit; i++) {
				if (History[(index-i+NUM_HISTORY)
					%NUM_HISTORY]==Command[c].Input[j]) break;
			}
			if (i==Command[c].Limit) break;
		}
		
		// R}?hÌüÍ¸mmFÅª½½F
		// R}?hV?ªógð?¿C?ððN?¥Â·éB
		// ïÌIÈ??ÍComShotÖ?Ås´ÓÆ·éB
		if (j==-1) {
			ComShot(j);
			for (i=0; i<NUM_HISTORY; i++) History[i]=NONE;
		}
	}
	
	// L^ÊuðXöè·é
	index=(index+1)%NUM_HISTORY;
}

