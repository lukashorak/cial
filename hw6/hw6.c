#include<stdio.h>
#include <string.h>
/*DECLARATIONS*/
#define DEBUG 1
#define N 1000
/*DEFINITIONS*/

struct number {
	float f;
	double d;
};

union number_union {
	float f;
	double d;
};

union number_union_32 {
	uint32_t i;
	float f;
};

union number_union_64 {
	uint64_t l;
	double d;
};

struct number_bitfield {
	unsigned int i :32;
//unsigned long l :64;
};
struct number_bitfield_32_pattern {
	unsigned int sign :1;
	unsigned int exp_sign :1;
	unsigned int exp :7;
	unsigned int mantissa :23;
};

struct number_bitfield_64 {
	unsigned int sign :1;
	unsigned int exp_sign :1;
	unsigned int exp :10;
	unsigned long mantissa :52;
};

//assumes little endian
void printBits(size_t const size, void const * const ptr) {
	unsigned char *b = (unsigned char*) ptr;
	unsigned char byte;
	int i, j;

	for (i = size - 1; i >= 0; i--) {
		for (j = 7; j >= 0; j--) {
			byte = b[i] & (1 << j);
			byte >>= j;
			printf("%u", byte);
		}
	}
	puts("");
}


void print_bitpattern_double(double d) {
	//double decker = 1.0;
	unsigned char * desmond = (unsigned char *) &d;
	int i;

	for (i = 0; i < sizeof(double); i++) {
		printf("%08X ", desmond[i]);
	}
	printf("\n");
}

void print_bitpattern_float(float d) {
	//double decker = 1.0;
	unsigned char * desmond = (unsigned char *) &d;
	int i;

	for (i = 0; i < sizeof(float); i++) {
		printf("%08X ", desmond[i]);
	}
	printf("\n");
}

void convert_union_32(char *word, int flag_to_binary) {
	int len = strlen(word);

	printf("Word : %s\n", word);
	printf("Len : %d\n", len);

	if (flag_to_binary) {

		float f;
		sscanf(word, "%f", &f);
		union number_union_32 u_float;
		u_float.f = f;
		printf("Float is : %f\n", u_float.f);
		printf("Decimal is : %d\n", u_float.i);
		printBits(sizeof(u_float.i), &(u_float.i));
	} else {
		int i = 0;
		unsigned long r = 0;
		char * bin = word;
		for (i = 0; i < len; i++) {
			r = r * 2 + (bin[i] == '1' ? 1 : 0);
		}

		union number_union_32 u_float;
		u_float.i = r;
		printf("Float is : %f\n", u_float.f);
		printf("Decimal is : %d\n", u_float.i);
	}
	printf("\n");
}

void convert_union_64(char *word, int flag_to_binary) {
	int len = strlen(word);

	printf("Word : %s\n", word);
	printf("Len : %d\n", len);

	if (flag_to_binary) {
		double d;
		sscanf(word, "%lf", &d);
		union number_union_64 u_double;
		u_double.d = d;
		printf("Float is : %f\n", u_double.d);
		printf("Decimal is : %d\n", u_double.l);
		printBits(sizeof(u_double.l), &(u_double.l));
	} else {
		int i = 0;
		unsigned long r = 0;
		char * bin = word;
		for (i = 0; i < len; i++) {
			r = r * 2 + (bin[i] == '1' ? 1 : 0);
		}
		union number_union_64 u_doule;
		u_doule.l = r;
		printf("Double is : %f\n", u_doule.d);
		printf("Decimal is : %lu\n", r);
	}
	printf("\n");
}

void convert_pointer_32(char *word, int flag_to_binary) {
	int len = strlen(word);

	printf("Word : %s\n", word);
	printf("Len : %d\n", len);

	if (flag_to_binary) {

		float f;
		sscanf(word, "%f", &f);
		//Pointer to float
		float *p;
		//long variable
		uint32_t r = 0;
		//Make the pointer point to the address where the long r is
		p = &r;
		//Change the value where pointer p points (the float f), but treat it as it is unsigned long
		*p = f;

		printf("Float is : %f\n", f);
		printf("Decimal is : %d\n", r);
		printBits(sizeof(r), &(r));
	} else {
		int i = 0;
		unsigned long r = 0;
		char *bin = word;
		for (i = 0; i < len; i++) {
			r = r * 2 + (bin[i] == '1' ? 1 : 0);
		}

		//Pointer
		int *p;
		//Float variable
		float f;
		//Make the pointer point to the address where the float f is
		p = &f;
		//Change the value where pointer p points (the float f), but treat it as it is unsigned long
		*p = r;

		printf("Float is : %f\n", f);
		printf("Decimal is : %d\n", r);
	}
	printf("\n");
}

void convert_pointer_64(char *word, int flag_to_binary) {
	int len = strlen(word);

	printf("Word : %s\n", word);
	printf("Len : %d\n", len);

	if (flag_to_binary) {
		double f;
		sscanf(word, "%lf", &f);
		//Pointer to float
		double *p;
		//long variable
		uint64_t r = 0;
		//Make the pointer point to the address where the long r is
		p = &r;
		//Change the value where pointer p points (the float f), but treat it as it is unsigned long
		*p = f;

		printf("Double is : %f\n", f);
		printf("Decimal is : %d\n", r);
		printBits(sizeof(r), &(r));
	} else {

		int i = 0;
		uint64_t r = 0;
		char * bin = word;
		for (i = 0; i < len; i++) {
			r = r * 2 + (bin[i] == '1' ? 1 : 0);
		}


		//Pointer
		long *p;
		//Double variable
		double d;
		//Make the pointer point to the address where the double d is
		p = &d;
		//Change the value where pointer p points (the double d), but treat it as it is unsigned long
		*p = r;

		printf("Double is : %f\n", d);
		printf("Decimal is : %lu\n", r);
	}
	printf("\n");
}

void convert_bit_field_32() {
	//char word[64];
	//scanf("%s", &word);
	//char word[] = "1101";
	char word[] = "00111111110000000000000000000000";

	//fgets(word, 63, stdin);
	//word[63] = 0;
	int len = strlen(&word);

	printf("Word : %s\n", word);
	printf("Len : %d\n", len);

	int i = 0;
	unsigned long r = 0;
	char * bin = &word;
	for (i = 0; i < len; i++) {
		r = r * 2 + (bin[i] == '1' ? 1 : 0);
	}
	printf("Decimal is : %d\n", r);

	float f;

	printf("Float is : %f\n", f);
	printf("\n");
}

int read_input(char *value, int flag_32bit) {
	char word[64] = "";
	scanf("%s", &word);
	int len = strlen(&word);

	int flag_binary = 1;

	int flag_floating = 0;

	int i;
	for (i = 0; i < len; i++) {
		char c = word[i];
		if (c != '0' && c != '1') {
			flag_binary = 0;
		}
		printf("%c ", c);
	}

	if (flag_binary) {
		if (flag_32bit) {
			int n = 32 - len;
			char zeros[32] = "";

			for (i = 0; i < n; i++) {
				strcat(zeros, "0");
			}
			strcat(zeros, word);
			strcpy(word, zeros);
		} else {
			int n = 64 - len;
			char zeros[64] = "";

			for (i = 0; i < n; i++) {
				strcat(zeros, "0");
			}
			strcat(zeros, word);
			strcpy(word, zeros);
		}
	}

	double d;
	if (sscanf(word, "%lf", &d) == 1) {
		flag_floating = 1;
	}

	printf("\n");
	printf("Word :%s\n", word);
	printf("Word filled:%s\n", word);
	printf("Len :%d\n", len);
	printf("flag_binary :%d\n", flag_binary);
	printf("flag_floating :%d\n", flag_floating);
	printf("Floating conversion 64:%.10lf\n", d);
	printf("Floating conversion 32:%.10f\n", (float) d);

	strcpy(value, word);
	printf("Value :%s\n", value);
	printf("\n");

	if (flag_binary) {
		return 1;
	}
	if (flag_floating) {
		return 0;
	} else {
		return -1;
	}
}
int main(int argc, char **argv) {
	setvbuf(stdout, NULL, _IONBF, 0);
	printf("Use 32bit(1) or 64bit(0) :\n");
	int flag_32bit = 1;
	scanf("%c",&flag_32bit);

	printf("Write input to convert 1. floating point number 1.9 or binary representation:\n");
	char word[64];
	char *w = word;
	//word = w;
	int flag_from_binary_to_floating = read_input(w, flag_32bit);
	printf("Word outside :%s\n\n", w);

	if (flag_from_binary_to_floating) {
		printf("flag_from_binary_to_floating TRUE\n");
		if (flag_32bit) {
			printf("Pointer - 32bit Float\n");
			convert_pointer_32(w, 0);
			printf("\n");
			printf("Union - 32bit Float\n");
			convert_union_32(w, 0);
			printf("\n");
		} else {
			printf("Pointer - 64bit Double\n");
			convert_pointer_64(w, 0);
			printf("\n");
			printf("Union - 64bit Double\n");
			convert_union_64(w, 0);
			printf("\n");
		}
	} else {
		printf("flag_from_binary_to_floating FALSE\n");
		if (flag_32bit) {
			printf("Pointer - 32bit Float\n");
			convert_pointer_32(w, 1);
			printf("\n");
			printf("Union - 32bit Float\n");
			convert_union_32(w, 1);
			printf("\n");
		} else {
			printf("Pointer - 64bit Double\n");
			convert_pointer_64(w, 1);
			printf("\n");
			printf("Union - 64bit Double\n");
			convert_union_64(w, 1);
			printf("\n");
		}
	}

	printf("\n");
	return 0;
}
