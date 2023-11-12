// ��`��?���蔻�]��\���\����
typedef struct {
	float Left, Top, Right, Bottom;
} HIT;

// ���G��?���蔻�]��\���\����
#define MAX_HIT 32
typedef struct {
	HIT* Hit[MAX_HIT];  // ��`��?���蔻�]
	int Num;            // ?���蔻�]�̌�?
} COMPLEX_HIT;

// �u��`�v�I�u��`�v�̊�{�I��?���蔻�]??
bool IsHit(HIT* a, HIT* b) {
	return
		a->Left<b->Right && b->Left<a->Right && 
		a->Top<b->Bottom && b->Top<a->Bottom;
}

// �u��`�v�I�u���G�Ȍ`�v��?���蔻�]??�F
// ��?�̋�`�ɤI����?��?���蔻�]??���s���C
// �����ꂩ�ɂ��ď�?�m����������u?����v�Ƃ���B
bool IsHit(COMPLEX_HIT* a, HIT* b) {
	for (int i=0; i<a->Num; i++) {
		if (IsHit(a->Hit[i], b)) return true;
	}
	return false;
}

// �u���G�Ȍ`�v�I�u���G�Ȍ`�v��?���蔻�]??�F
// �S�Ă̑g��?�킹�ɂ���?���蔻�]??���s���C
// �����ꂩ�̑g��?�킹�ŏ�?�m����������u?����v�Ƃ���B
bool IsHit(COMPLEX_HIT* a, COMPLEX_HIT* b) {
	for (int i=0; i<a->Num; i++) {
		for (int j=0; j<b->Num; j++) {
			if (IsHit(a->Hit[i], b->Hit[j])) return true;
		}
	}
	return false;
}

