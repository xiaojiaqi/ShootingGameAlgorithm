// �X�e�B��N�ƃ{�^?�̓��͂�\���]?�F
// �e���͂�1�r��g�ŕ\���B
enum {
	UP=1, DOWN=2, LEFT=4, RIGHT=8,
	BUTTON1=16, BUTTON2=32
} INPUT;

// ?�v?�C�f�[�^����������\���́F
// �X�e�B��N�ƃ{�^?�̓��͂���������B
#define MAX_TIME 10000
typedef struct {
	char Input[MAX_TIME];
} REPLAY_DATA;

// ���@�𓮂���
void MoveMyShip(
	char input,                // �X�e�B��N�ƃ{�^?�̓���
	bool is_replay,            // ?�v?�C?�Ȃ��true
	REPLAY_DATA* replay_data,  // ?�v?�C�f�[�^
	int& time                  // �^�C�}�[
) {
	// ?�v?�C��??�F
	// ?�v?�C?�Ȃ�Γ��͂�?�v?�C�f�[�^����ï�ݏo���B
	// ?�v?�C?�łȂ����?�v?�C�f�[�^�ɓ��͂���������B
	if (is_replay) {
		input=replay_data->Input[time];
	} else {
		replay_data->Input[time]=input;
	}
	
	// �^�C�}�[��i�߂�
	time++;

	// ���͂ɏ]���Ď��@�𓮂����F
	// �ړ����?�̋�̓I��??�́C
	// MoveUp�CMoveDown�CMoveLeft�CMoveRight�C
	// Shot�CLaser�̊e��?�ōs�ӂƂ���B
	if (input&UP   ) MoveUp();
	if (input&DOWN ) MoveDown();
	if (input&LEFT ) MoveLeft();
	if (input&RIGHT) MoveRight();
	if (input&BUTTON1) Shot();
	if (input&BUTTON2) Laser();
}

