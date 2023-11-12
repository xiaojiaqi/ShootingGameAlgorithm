//============================================================== (1)
// �X�e�B��N�ƃ{�^?�̏��Ԃ�\���]?�F
// 2�ȏ�̃]?��g��?�킹�����Ƃ��Ū���B
// ��V�΁u����v�́C
// �u��v�Ɓu���v�̑g��?�킹�iUP|LEFT�j�ŕ\���B
#define NONE     0  // ?������
#define NEUTRAL  1  // �j?�[�g??
#define UP       2  // ��
#define DOWN     4  // ��
#define LEFT     8  // ��
#define RIGHT   16  // ��
#define BUTTON  32  // �{�^?

// ����?���̌�?�C����?��
#define NUM_HISTORY 30
static int History[NUM_HISTORY];

// �R�}?�h
typedef struct {
	int Length;              // �R�}?�h�̒���
	int Limit;               // ����?�Ԃ̐���
	int Input[NUM_HISTORY];  // ���ͅ��e
} COMMAND_TYPE;
#define NUM_COMMAND 2
COMMAND_TYPE Command[NUM_COMMAND];

//============================================================== (2)
// ����?���ƃR�}?�h��?����
void InitCommandShot()
{
	// ����?����?����
	for (int i=0; i<NUM_HISTORY; i++) History[i]=NONE;

	// �R�}?�h1�i�g��?�R�}?�h�j
	Command[0].Length=4;
	Command[0].Limit=30;
	Command[0].Input[0]=DOWN;
	Command[0].Input[1]=DOWN|RIGHT;
	Command[0].Input[2]=RIGHT;
	Command[0].Input[3]=BUTTON;

	// �R�}?�h2�i����?�R�}?�h�j
	Command[1].Length=4;
	Command[1].Limit=30;
	Command[1].Input[0]=RIGHT;
	Command[1].Input[1]=DOWN;
	Command[1].Input[2]=DOWN|RIGHT;
	Command[1].Input[3]=BUTTON;
}

//============================================================== (3)
// �R�}?�h�V?��g�̔��]���s�ӊ�?
void CommandShot(
	bool up, bool down,     // �X�e�B��N�̏��ԁi�㉺�����j
	bool left, bool right,  
	bool button             // �{�^?�̏��ԁi?���ꂽ�ƪ�true�j
) {
	// ����?���̋L�^�ʒu
	static int index=0;
	
	// ���͂�?���ɋL�^����
	History[index]=
		(up?UP:0)|(down?DOWN:0)|
		(left?LEFT:0)|(right?RIGHT:0)|
		(button?BUTTON:0);

	// �e�R�}?�h�m���͂��ꂽ���Ǵӂ��𔻃]����
	int c, j, i;
	for (c=0; c<NUM_COMMAND; c++) {
		for (i=0, j=Command[c].Length-1; j>=0; j--) {
			for (; i<Command[c].Limit; i++) {
				if (History[(index-i+NUM_HISTORY)
					%NUM_HISTORY]==Command[c].Input[j]) break;
			}
			if (i==Command[c].Limit) break;
		}
		
		// �R�}?�h�̓��͸m�m�F�Ū����F
		// �R�}?�h�V?��g��?���C?�����N?����B
		// ��̓I��??��ComShot��?�ōs�ӂƂ���B
		if (j==-1) {
			ComShot(j);
			for (i=0; i<NUM_HISTORY; i++) History[i]=NONE;
		}
	}
	
	// �L�^�ʒu���X�肷��
	index=(index+1)%NUM_HISTORY;
}

