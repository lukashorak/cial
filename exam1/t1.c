#include <stdio.h>

struct person {
	char lastname[10];
	char firstname[16];
	unsigned sex :1;
	unsigned age :6;
	unsigned day :5;
	unsigned month :4;
	unsigned year :7;
	unsigned :0;
	unsigned IP;
	char cellphone[5];
};

void main(char** args) {
	setvbuf(stdout, NULL, _IONBF, 0);

	struct person p1 = { 'Chang', 'Michael', 0, 50, 24, 12, 113, 123456,
			'12345' };

	printf("%s %d %d %d\n", p1.lastname, p1.sex, p1.age, p1.month);
	printf("Finished");
}
