// ??�̎�
typedef unsigned int ulong;
static ulong seed=1;

// ���?����
void srand(ulong s) {
	seed=s;
}

// ??�̐���
ulong rand() {
	seed=seed*48828125UL+1;
	return seed;
}
