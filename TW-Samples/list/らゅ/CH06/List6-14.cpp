// �{�X��\���\����
#define MAX_PART 32
#define MAX_FORM 8
typedef struct BOSS_STRUCT {
	float X, Y;                  // �{�X�̍��W
	struct BOSS_STRUCT* 
		Part[MAX_PART];          // �{�X���\������p�[�c�i�{�X�j
	int NumPart;                 // �p�[�c��?
	float 
		PX[MAX_PART][MAX_FORM],  // �p�[�c��?�I���W
		PY[MAX_PART][MAX_FORM];  // [�p�[�c��?][�`�Ԕ�?]
} BOSS;

// �ό`�F
// �e�p�[�c��ό`�O�̈ʒu����ό`��̈ʒu�ֈړ�������B
// �ό`�Ɋ|����?�Ԃƃ^�C�}�[�Ƃ̔䗦����C
// �ړ��r?�̈ʒu���v�Z����B
#define TRANSFORM_TIME 180
void TransformBoss(
	BOSS* boss,  // �{�X�̍\���̂ւ̃|�C?�^
	int from,    // �ό`�O�̌`�Ԕ�?
	int to,      // �ό`��̌`�Ԕ�?
	int& timer   // �^�C�}�[
) {
	float ratio=(float)timer/TRANSFORM_TIME;
	for (int i=0; i<boss->NumPart; i++) {
		boss->Part[i]->X=
			boss->PX[i][from]*(1-ratio)+
			boss->PX[i][to]*ratio;
		boss->Part[i]->Y=
			boss->PY[i][from]*(1-ratio)+
			boss->PY[i][to]*ratio;
	}
}

