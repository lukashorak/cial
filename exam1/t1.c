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
	//setvbuf(stdout, NULL, _IONBF, 0);

	printf("Input filename:");
	char filename[64] = "online_test.dat";
	//scanf("%s", &filename);
	printf("%s\n", filename);

	FILE *fr;
	fr = fopen(filename, "rt");

	int linePos = 0;
	char line[81];
	unsigned int plen;
	unsigned long ip;

	while (fgets(line, 80, fr) != NULL) {

		char l[10] = "";
		char f[16] = "";
		char s[6] = "";
		unsigned age;
		unsigned day;
		unsigned month;
		unsigned year;
		char phone[10] = "";
		unsigned ip1;
		unsigned ip2;
		unsigned ip3;
		unsigned ip4;

		sscanf(line, "%s %s %s %u %u %u %u %s %u.%u.%u.%u", &l, &f, &s, &age, &day, &month, &year, &phone, &ip1, &ip2, &ip3, &ip4);
		printf("%s %s %s %u %u %u %u %s %u.%u.%u.%u\n", l, f, s, age, day, month, year, phone, ip1, ip2, ip3, ip4 );

		unsigned sex = strcmp (s,"female");
		struct person p_in = {&l,&f,sex,age,day,month,year};

		printf("%s %s %u %u\n", p_in.lastname, p_in.firstname, p_in.sex, p_in.age);

	}

	fclose(fr); /* close the file prior to exiting the routine */

	struct person p1 =
			{ "Chang", "Michael", 0, 50, 24, 12, 113, 123456, "12345" };
	printf("%x\n", p1.month);
	printf("%s %d %d %d\n", p1.lastname, p1.sex, p1.age, p1.month);
	printf("Finished");
}
