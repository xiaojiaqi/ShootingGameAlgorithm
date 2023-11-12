#include <stdio.h>

// ??
#define N 15

// ?�����i���{��?��?�j
void init(char a[], int x) {
	int t=x;
	for (int i=N-1; i>=0; i--) {
		a[i]=t%10;
		t/=10;
	}
}

// ���Z�i���{���{��?�j
void add(char a[], int x) {
	int t=x;
	for (int i=N-1; i>=0; i--) {
		t+=a[i];
		a[i]=t%10;
		t/=10;
	}
}

// ���Z�i���{���{���{���j
void add(char a[], char b[]) {
	int t=0;
	for (int i=N-1; i>=0; i--) {
		t+=a[i]+b[i];
		a[i]=t%10;
		t/=10;
	}
}

// ��Z�i���{���~��?�j
void mul(char a[], int x) {
	int t=0;
	for (int i=N-1; i>=0; i--) {
		t+=x*a[i];
		a[i]=t%10;
		t/=10;
	}
}

// �\��
void print(char a[]) {
	int i;
	for (i=0; i<N-1 && a[i]==0; i++);
	for (; i<N; i++) printf("%d", a[i]);
}

// ?�C?
void main(int, char*[]) {
	int x;
	
	// ���{��?��\���z��
	char a[N], b[N];

	// ���{���{��?
	init(a, 87654321);
	printf("a: "); print(a); printf("\n");
	add(a, x=12345679);
	printf("a+=%d: ", x); print(a); printf("\n");
	printf("\n");

	// ���{���{���{��
	init(a, 123456789);
	init(b, 987654321);
	printf("a: "); print(a); printf("\n");
	printf("b: "); print(b); printf("\n");
	add(a, b);
	printf("a+=b: "); print(a); printf("\n");
	printf("\n");

	// ���{���~��?
	init(a, 987654321);
	printf("a: "); print(a); printf("\n");
	mul(a, x=1000000);
	printf("a*=%d: ", x); print(a); printf("\n");
}

