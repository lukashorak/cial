#include<stdio.h>
/*DECLARATIONS*/
#define DEBUG 1
#define N 1000
#define BYTETOBINARYPATTERN "%d%d%d%d%d%d%d%d"
#define BYTETOBINARY(byte)  \
  (byte & 0x80 ? 1 : 0), \
  (byte & 0x40 ? 1 : 0), \
  (byte & 0x20 ? 1 : 0), \
  (byte & 0x10 ? 1 : 0), \
  (byte & 0x08 ? 1 : 0), \
  (byte & 0x04 ? 1 : 0), \
  (byte & 0x02 ? 1 : 0), \
  (byte & 0x01 ? 1 : 0)
/* note semi-colon here */
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

int input_pointer() {

	return 1;
}

int input_union() {

}

int input_bit_field() {

}

void run_test() {
	float f1, f2, f3;
	f1 =
			1.175494350822287507968736537222245677818665556772087521508751706278417259454727172851560500000000000000000000000000000000e-38f;
	f2 = 1.175494350822287500e-38f;
	f3 = 0x00800000;
	print_bitpattern_float(f1);
	print_bitpattern_float(f2);
	print_bitpattern_float(f3);

	if (f1 == f2) {
		printf("%100e = %100e", f1, f2);
	} else {
		printf("%100e != %100e", f1, f2);
	}
	printf("\n");
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

int main(int argc, char **argv) {
	setvbuf(stdout, NULL, _IONBF, 0);

	run_test();

	union number_union_32 uf;

	uf.f = 1.234f;

	printf("%d", uf.i);
	printf("\n");
	printf("%e", uf.f);

	printf("\n");
	printf("\n");
	//float i = 1.234f;
	printBits(sizeof(uf.i), &(uf.i));

	union number_union_64 ud;

	ud.d = 1.2345678;
	printBits(sizeof(ud.l), &(ud.l));
	printf("\n");

	struct number_bitfield bf;

	float f_value = 1.234f;
	bf.i = *(int*)&f_value;
	printBits(4, &bf);
}
int main2(int argc, char **argv) {
	setvbuf(stdout, NULL, _IONBF, 0);
	//float f1, f2;

	//int byte = 10;
	//char byte = 10;
	run_test();

	float in_float;
	double in_double;
	//char str[255];

	//char str [] = "1.23";
	char str[] = "1.23456789";
	printf("Input 1. float or double number 2. bit pattern :\n>");
	//scanf("%s", &str);

	sscanf(str, "%f", &in_float);
	sscanf(str, "%lf", &in_double);
	printf("========================\n");
	printf("%15.15e\n%15.15e\n", in_float, in_double);
	printf("========================\n");

	//in_float = (float) in_double;
	if (in_float == (float) in_double) {
		printf("%.5e == %e", in_float, in_double);
	} else {
		printf("%.5e != %e", in_float, in_double);
	}
	printf("\n");

	float M = 1.0f;
	//M = 1.175494350822287500e-38f;
	//printf("Leading text :"BYTETOBINARYPATTERN, BYTETOBINARY(byte));
	//printf("M: "BYTETOBINARYPATTERN" "BYTETOBINARYPATTERN"\n",
	//		BYTETOBINARY(M >> 8), BYTETOBINARY(M));
	print_bitpattern_float(M);
	printf("\n");
	union {
		int i;
		float f;
	} u;

	// Convert floating-point bits to integer:
	u.f = 3.14159f;
	printf("As integer: %08x\n", u.i);
	u.i = 1234567890;
	printf("As float: %f\n", u.f);
	printf("finished");
	return 0;
}
