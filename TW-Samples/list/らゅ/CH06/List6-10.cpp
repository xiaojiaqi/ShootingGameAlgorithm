// 矩形の?たり判ゾを表す構造体
typedef struct {
	float Left, Top, Right, Bottom;
} HIT;

// 複雑な?たり判ゾを表す構造体
#define MAX_HIT 32
typedef struct {
	HIT* Hit[MAX_HIT];  // 矩形の?たり判ゾ
	int Num;            // ?たり判ゾの個?
} COMPLEX_HIT;

// 「矩形」､I「矩形」の基本的な?たり判ゾ??
bool IsHit(HIT* a, HIT* b) {
	return
		a->Left<b->Right && b->Left<a->Right && 
		a->Top<b->Bottom && b->Top<a->Bottom;
}

// 「矩形」､I「複雑な形」の?たり判ゾ??：
// 複?の矩形に､Iして?に?たり判ゾ??を行い，
// いずれかについて条?ｸm成立したら「?たり」とする。
bool IsHit(COMPLEX_HIT* a, HIT* b) {
	for (int i=0; i<a->Num; i++) {
		if (IsHit(a->Hit[i], b)) return true;
	}
	return false;
}

// 「複雑な形」､I「複雑な形」の?たり判ゾ??：
// 全ての組み?わせについて?たり判ゾ??を行い，
// いずれかの組み?わせで条?ｸm成立したら「?たり」とする。
bool IsHit(COMPLEX_HIT* a, COMPLEX_HIT* b) {
	for (int i=0; i<a->Num; i++) {
		for (int j=0; j<b->Num; j++) {
			if (IsHit(a->Hit[i], b->Hit[j])) return true;
		}
	}
	return false;
}

