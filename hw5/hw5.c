#include<stdio.h>
/*DECLARATIONS*/
#define N 1000
#define DEBUG 0
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

unsigned long pow(int a, int b) {
	unsigned long v = a;
	int i;
	for (i = 0; i < b; i++) {
		v = v * a;
	}

	return v;
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
		if (DEBUG)
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
		if (DEBUG)
			printf("%d.%d.%d.%d/(%d)\t", p1, p2, p3, p4, *len);
		return 1;
	}
	return 0;
}

unsigned long combine_ip(int p1, int p2, int p3, int p4) {
	unsigned long ip = (p1 << 24) + (p2 << 16) + (p3 << 8) + p4;
	return ip;
}
void print_ip_with_len(long ip, int len) {
	unsigned char bytes[4];
	bytes[0] = ip & 0xFF;
	bytes[1] = (ip >> 8) & 0xFF;
	bytes[2] = (ip >> 16) & 0xFF;
	bytes[3] = (ip >> 24) & 0xFF;
	printf("%d.%d.%d.%d/%d", bytes[3], bytes[2], bytes[1], bytes[0], len);
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
		if (DEBUG) {
			printf("%d\t", linePos);
		}
		//printf(line);
		if (char_to_ip(line, &ip, &plen)) {
			IP[linePos] = ip;
			Len[linePos] = plen;
			linePos++;
		} else {
			puts("ERROR");
		}
		if (DEBUG) {
			printf("%lu /%d\n", ip, plen);
		}
	}
	//printf("Total number of prefixes in input file:%d\n", linePos);
	fclose(fr); /* close the file prior to exiting the routine */
	*lineCount = linePos;
	return 1;
}

int length_distribution(int size, unsigned int Len[], unsigned int Dist[33]) {
	int i;
	for (i = 0; i < size; i++) {
		int l = Len[i];
		//printf("%d\t%d\n", i, l);
		Dist[l] = (Dist[l] + 1);
	}

	printf("\n====\n");
	for (i = 0; i < 33; i++) {
		printf("%u\t%5u\n", i, Dist[i]);
	}
	printf("====\n");
	for (i = 0; i < 33; i++) {
		printf("%5u ", i);
	}
	printf("\n");
	for (i = 0; i < 33; i++) {
		printf("%5u ", Dist[i]);
	}
	printf("\n");
	return 1;
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
		//printf("\n");
	}

	printf("======\n");
	for (i = 0; i < size; i++) {
		if (DEBUG) {
			print_ip_with_len(IP[i], Len[i]);
			printf("  \t");
		}
		//printBits((int) IP[i], d);
		process((long) IP[i], d);

		if (Len[i] < d) {
			if (DEBUG)
				printf("Don't fit\t");
			unsigned long m = ((long) IP[i] >> (32 - d + 1));
			int s = max(0, d - Len[i]);
			for (j = 0; j < groupCount; j++) {
				unsigned long g = ((long) group[j] >> s);
				int c = (m == g);
				if (c != 0) {
					if (DEBUG)
						printf("%d %d %d\t", m, s, g);
					groupContain[j]++;
				}
			}

		} else {
			unsigned long m = ((int) IP[i] >> (32 - d + 1));
			for (j = 0; j < groupCount; j++) {
				int c = (m == group[j]);
				if (c != 0) {
					if (DEBUG)
						printf("\t\t%d  %d  %d", m, group[j], c);
					groupContain[j]++;
				}
			}
		}
		if (DEBUG)
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

	if (DEBUG)
		printf("%u\t %u\t %u\t", i, j, m);
}

int main(int argc, char **argv) {
	setvbuf(stdout, NULL, _IONBF, 0);

	//char* fileName = "in.txt";
	//char* fileName = "sample.txt";
	char* fileName = "oix80k";

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
		if (DEBUG) {
			print_ip_with_len(IP[i], Len[i]);
			printf("\t -->\t%lu\n", IP[i]);
		}
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
	puts("start5 - segment groups");

	unsigned int d = input_segments();
	int works5 = segment(d, lineCount, &IP, &Len);
	if (!works5) {
		puts("ERROR - 5");
		return 1;
	}

	puts("finished5");
	return 0;
}
