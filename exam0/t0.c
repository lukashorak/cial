#include<stdio.h>
#include <string.h>

union floatlong {
	float f;
	int l;
};

void printIntBits(int value) {

	int size = sizeof(value);

	int i, j;
	unsigned char *b = (unsigned char*) value;
	unsigned char byte;

	for (i = size - 1; i >= 0; i--) {
		for (j = 7; j >= 0; j--) {
			byte = b[i] & (1 << j);
			byte >>= j;
			printf("%u", byte);
		}
	}
}

void main(char** args) {
	setvbuf(stdout, NULL, _IONBF, 0);
	union floatlong u;
	printf("Please input floating number:");
	scanf("%f", &u.f);

	printf("%f\n%d\n", u.f, u.l);

	printIntBits(&(u.l));
}
