// ??‚Ìí
typedef unsigned int ulong;
static ulong seed=1;

// í‚Ì?Šú‰»
void srand(ulong s) {
	seed=s;
}

// ??‚Ì¶¬
ulong rand() {
	seed=seed*48828125UL+1;
	return seed;
}
