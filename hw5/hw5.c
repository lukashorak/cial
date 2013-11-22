#include<stdio.h>
#include<math.h>
/*DECLARATIONS*/
#define N 1000
/*DEFINITIONS*/

//Min function - compare two numbers and return the copy of the smaller
int min(int a, int b) {
	if (a > b) {
		return b;
	} else {
		return a;
	}
}
//Max function - compare two numbers and return the copy of the larger
int max(int a, int b) {
	if (a >= b) {
		return a;
	} else {
		return b;
	}
}

unsigned int input_segments() {
	//Initialize variables
	unsigned int n;
	puts("Number of bits of same prefix :");
	scanf("%u", &n);
	if (n < 0 || n > 32) {
		printf("n have to be between 0 and 32");
		return -1;
	}

	return n;
}

int scan_number_of_lines(char* fileName, int *lc) {
	FILE *fr;

	fr = fopen(fileName, "rt");
	if (fr == 0) {
		return 0;
	}
	char line[280];

	int lineCount = 0;
	/* get a line, up to 80 chars from fr.  done if NULL */
	while (fgets(line, 280, fr) != NULL) {
		lineCount++;
	}

	fclose(fr);
	*lc = lineCount;
	return 1;
}

unsigned long char_to_ip(char* str, unsigned long *ip, unsigned int *len) {
	unsigned int p1, p2, p3, p4, plen;

	int result = sscanf(str, "%d.%d.%d.%d/%d", &p1, &p2, &p3, &p4, &plen);
	if (result == 5) {
		printf("%d.%d.%d.%d/%d\t", p1, p2, p3, p4, plen);
		*ip = (p1 << 24) + (p2 << 16) + (p3 << 8) + p4;
		*len = plen;
		return 1;
	} else if (result == 4) {
		//In case the len is missing
		*ip = (p1 << 24) + (p2 << 16) + (p3 << 8) + p4;
		*len = 32;
		if (p4 == 0) {
			*len = 24;
			if (p3 == 0) {
				*len = 16;
				if (p2 == 0) {
					*len = 8;
				}
			}
		}
		printf("%d.%d.%d.%d/(%d)\t", p1, p2, p3, p4, *len);
		return 1;
	}
	return 0;
}

unsigned long combine_ip(int p1, int p2, int p3, int p4) {
	unsigned long ip = (p1 << 24) + (p2 << 16) + (p3 << 8) + p4;
	return ip;
}
void print_ip(int ip) {
	unsigned char bytes[4];
	bytes[0] = ip & 0xFF;
	bytes[1] = (ip >> 8) & 0xFF;
	bytes[2] = (ip >> 16) & 0xFF;
	bytes[3] = (ip >> 24) & 0xFF;
	printf("%d.%d.%d.%d", bytes[3], bytes[2], bytes[1], bytes[0]);
}
void print_ip_with_len(long ip, int len) {
	unsigned char bytes[4];
	bytes[0] = ip & 0xFF;
	bytes[1] = (ip >> 8) & 0xFF;
	bytes[2] = (ip >> 16) & 0xFF;
	bytes[3] = (ip >> 24) & 0xFF;
	printf("%d.%d.%d.%d/%d", bytes[3], bytes[2], bytes[1], bytes[0], len);
}

int mainTest(int argc, char **argv) {
	setvbuf(stdout, NULL, _IONBF, 0);
	FILE *fr;
	char* fileName = "in.txt";

	puts("start1");

	fr = fopen(fileName, "rt");
	int l = 99;
	if (!scan_number_of_lines(fileName, l)) {
		puts("ERROR");
	}

	printf("Lines = %d\n", l);

	puts("finished1");
	puts("start2");

	char* lineTest = "1.2.3.4/22";

	unsigned int plen;
	unsigned long ip;

	if (!char_to_ip(lineTest, &ip, &plen)) {
		puts("ERROR");
	}

	printf("%l\n", ip);
	print_ip_with_len(ip, plen);
	puts("finished2");

	fclose(fr); /* close the file prior to exiting the routine */
	return 0;
}

int input(char* fileName, int size, int *lineCount, unsigned long IP[],
		unsigned int Len[]) {
	FILE *fr;
	fr = fopen(fileName, "rt");

	int linePos = 0;
	char line[81];
	unsigned int plen;
	unsigned long ip;

	while (fgets(line, 80, fr) != NULL) {
		printf("%d\t", linePos);
		//printf(line);
		if (char_to_ip(line, &ip, &plen)) {
			IP[linePos] = ip;
			Len[linePos] = plen;
			linePos++;
		} else {
			puts("ERROR");
		}
		printf("%lu /%d\n", ip, plen);
	}
	//printf("Total number of prefixes in input file:%d\n", linePos);
	fclose(fr); /* close the file prior to exiting the routine */
	*lineCount = linePos;
	return 1;
}

void print_number_of_prefixes() {

}

int length_distribution(int size, unsigned int Len[], unsigned int Dist[33]) {
	int i;
	for (i = 0; i < size; i++) {
		int l = Len[i];
		//printf("%d\t%d\n", i, l);
		Dist[l] = (Dist[l] + 1);
	}

	//printf("\n====\n");
	//for (i = 0; i < 33; i++) {
	//printf("%d\t%d\n", i, Dist[i]);
	//}
	printf("====\n");
	for (i = 0; i < 33; i++) {
		printf("%3u ", i);
	}
	printf("\n");
	for (i = 0; i < 33; i++) {
		printf("%3u ", Dist[i]);
	}
	printf("\n");
	return 1;
}

void printBits(unsigned int num, int maxBits) {
	int bit;
	for (bit = 0; (bit < (sizeof(unsigned int) * 8)) && (bit < maxBits);
			bit++) {
		printf("%i ", num & 0x01);
		num = num >> 1;
	}
}
void print_binary(int n, int maxBits) {
	if (maxBits <= 0)
		return;
	if (n == 0 || n == 1)
		printf("%d ", n);
	else {
		print_binary(n >> 1, --maxBits);
		printf("%d ", (n & 0x1));
	}
}

void printbits(int n) {
	unsigned int i, step;

	if (0 == n) /* For simplicity's sake, I treat 0 as a special case*/
	{
		printf("0000");
		return;
	}

	i = 1 << (sizeof(n) * 8 - 1);

	step = -1; /* Only print the relevant digits */
	step >>= 4; /* In groups of 4 */
	while (step >= n) {
		i >>= 4;
		step >>= 4;
	}

	/* At this point, i is the smallest power of two larger or equal to n */
	while (i > 0) {
		if (n & i)
			printf("1");
		else
			printf("0");
		i >>= 1;
	}
}

int segment(unsigned int d, int size, unsigned long IP[], unsigned int Len[]) {

	int i, j;
	int groupCount = pow(2, d);
	unsigned int group[groupCount];
	unsigned int groupContain[groupCount];

	//generate groups
	for (i = 0; i < groupCount; i++) {
		group[i] = i;
		groupContain[i] = 0;
		//printBits(i, d);
		//printf("\n");
	}

	printf("======\n");
	for (i = 0; i < size; i++) {
		print_ip_with_len(IP[i], Len[i]);
		printf("  \t");
		//printBits((int) IP[i], d);
		process((long) IP[i], d);

		if (Len[i] < d) {
			printf("Don't fit - TODO\t");
			unsigned long m = ((long) IP[i] >> (32 - d + 1));
			int s = max(0, d - Len[i]);
			for (j = 0; j < groupCount; j++) {
				unsigned long g = ((long) group[j] >> s);
				int c = (m == g);
				if (c != 0) {
					printf("%d %d %d\t", m, s, g);
					groupContain[j]++;
				}
			}

		} else {
			unsigned long m = ((int) IP[i] >> (32 - d + 1));
			for (j = 0; j < groupCount; j++) {
				int c = (m == group[j]);
				if (c != 0) {
					printf("\t\t%d  %d  %d", m, group[j], c);
					groupContain[j]++;
				}
			}
		}
		printf("\n");
	}
	printf("======\n");
	for (i = 0; i < groupCount; i++) {
		if (groupContain[i] > 0) {
			printf("%d  --  %d\t%d\n", i, group[i], groupContain[i]);
		}

	}

	return 1;
}

void process(unsigned long i, unsigned long d) {
	unsigned long mask = pow(2, d);
	unsigned long j = i >> d;
	unsigned long m = (i >> (32 - d + 1));

	printf("%u\t %u\t %u\t", i, j, m);
	//print_binary(j, 8);
	//printf("\n");
}
int main2(int argc, char **argv) {
	setvbuf(stdout, NULL, _IONBF, 0);

	/*0.0.0.0/8	 -->	0
	 0.2.64.0/15	 -->	147456
	 0.3.0.0/23	 -->	196608
	 0.3.8.0/22	 -->	198656
	 1.3.33.0/24	 -->	16982272
	 1.3.38.0/23	 -->	16983552
	 1.3.41.0/24	 -->	16984320
	 */
	unsigned int i1 = 0;
	unsigned int i2 = 147456;
	unsigned int i3 = 196608;
	unsigned int i4 = 198656;
	unsigned int i5 = 16982272;
	unsigned int i6 = 16983552;
	unsigned int i7 = 16984320;

	printf("\n");
	unsigned int d = 8;
	//int m = 0xFFFFFFFF;
	process(i1, d);
	process(i2, d);
	process(i3, d);
	process(i4, d);
	process(i5, d);
	process(i6, d);
	process(i7, d);

	printf("\n");
}

int main(int argc, char **argv) {
	setvbuf(stdout, NULL, _IONBF, 0);

	//char* fileName = "in.txt";
	char* fileName = "sample.txt";

	puts("start1 - scan file to get number of lines");
	int l = 99;
	int works1 = scan_number_of_lines(fileName, &l);
	if (!works1) {
		puts("ERROR - 1");
		return 1;
	}
	printf("Lines = %d\n", l);
	//int l = 99;
	puts("finished1");
	puts("start2");
	int lineCount = 0;
	unsigned long IP[l];
	unsigned int Len[l];
	int works2 = input(fileName, l, &lineCount, &IP, &Len);
	if (!works2) {
		puts("ERROR - 2");
		return 1;
	}
	printf("Total number of prefixes in input file:%d\n", lineCount);
	puts("finished2");
	puts("start3 - print conversion");
	int i;

	for (i = 0; i < lineCount; i++) {
		print_ip_with_len(IP[i], Len[i]);
		printf("\t -->\t%lu\n", IP[i]);
	}

	puts("finished3");
	puts("start4 - length distribution");
	unsigned int Dist[33] = { 0 };
	int works4 = length_distribution(lineCount, &Len, &Dist);
	if (!works4) {
		puts("ERROR - 4");
		return 1;
	}
	puts("finished4");
	puts("start5 - length distribution");

	unsigned int d = input_segments();
	int works5 = segment(d, lineCount, &IP, &Len);
	if (!works5) {
		puts("ERROR - 5");
		return 1;
	}

	puts("finished5");
	return 0;
}
