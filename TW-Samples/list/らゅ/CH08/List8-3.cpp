// ??の種
typedef unsigned int ulong;
static ulong seed=1;

// 種の?期化
void srand(ulong s) {
	seed=s;
}

// ??の生成
ulong rand() {
	seed=seed*48828125UL+1;
	return seed;
}
