#include<stdio.h>
#include<stdlib.h>
#include <string.h>

//DECLARATIONS

#define MAX_SIZE 10
#define BUCKET_SIZE 10

int min(int a, int b);
int max(int a, int b);
int bucket_union_array(int a[], int a_size, int b[], int b_size, int *u,
		int *u_size);
int scan_number_of_lines(char* fileName);
void readFromFile(char* fileName);
int new_mapping(int n, int l);

void printStartData();
void printFinalData();
//GLOBALS

static int data[MAX_SIZE][BUCKET_SIZE];
static int dataSize[MAX_SIZE];

static int dataFinal[MAX_SIZE][BUCKET_SIZE];
static int dataFinalSize[MAX_SIZE];
int maxBucketSize = 0;
//PROGRAM

int min(int a, int b) {
	if (a > b) {
		return b;
	} else {
		return a;
	}
}

int max(int a, int b) {
	if (a >= b) {
		return a;
	} else {
		return b;
	}
}

int bucket_union_array(int a[], int a_size, int b[], int b_size, int *u,
		int *u_size) {

	int bucket_size = 0;
	int bucket_union[BUCKET_SIZE];
	int i, j;

	for (i = 0; i < a_size; i++) {
		printf("%d ", a[i]);
	}
	printf(" --+-- ");
	for (i = 0; i < b_size; i++) {
		printf("%d ", b[i]);
	}
	printf("  ===  ");

	for (i = 0; i < a_size; i++) {
		bucket_union[i] = a[i];
		bucket_size++;
	}

	for (i = 0; i < b_size; i++) {
		int contain = 0;
		for (j = 0; j < bucket_size; j++) {
			if (b[i] == bucket_union[j]) {
				contain++;
			}
		}
		if (contain == 0) {
			bucket_union[bucket_size] = b[i];
			bucket_size++;
		}
	}

	for (i = 0; i < bucket_size; i++) {
		//b[i] = bucket_union[i];
		printf("%d ", bucket_union[i]);
	}
	printf("\n");
	//bucket.values = bucket_union;

	(*u_size) = bucket_size;
	for (i = 0; i < bucket_size; i++) {
		u[i] = bucket_union[i];
	}

	return bucket_size;
}
/*
 int scan_number_of_lines(char* fileName) {

 FILE *fr;
 fr = fopen(fileName, "rt");
 if (fr == NULL)
 perror("Error opening file");
 int c;
 unsigned long lineCount = 0;

 while ((c = fgetc(fr)) != EOF) {
 if (c == '\n')
 lineCount++;
 }

 printf("%lu newline characters\n", lineCount);

 return lineCount;
 }*/

void readFromFile(char* fileName) {
	FILE *fr;
	fr = fopen(fileName, "rt");

	int linePos = 0;
	//char line[280];
	char* line = malloc(sizeof(char) * 280);

	/* get a line, up to 80 chars from fr.  done if NULL */
	while (fgets(line, 280, fr) != NULL) {

		int fieldPos = 0;
		char* pch;

		printf("%d\t", linePos);
		pch = strtok(line, " ");
		while (pch != NULL) {
			int value;
			sscanf(pch, "%d", &value);

			data[linePos][fieldPos] = value;

			printf("%d ", value);
			pch = strtok(NULL, " ");
			fieldPos++;
		}
		dataSize[linePos] = fieldPos;
		printf("\t(%d)\n", dataSize[linePos]);
		linePos++;
		maxBucketSize = max(maxBucketSize, fieldPos);

	}

	printf("Max bucket size = %d\n", maxBucketSize);
	fclose(fr);
}

int test_bucket_union_array() {
	int n = 9;
	int a[] = { 1, 2, 7 };
	int a_size = 3;
	int b[] = { 2, 3, 4, 5 };
	int b_size = 4;
	int *u = malloc(sizeof(int) * 10);
	int *u_size;
	int r = bucket_union_array(a, a_size, b, b_size, u, &u_size);
	int result = (r <= n);
	printf("Result=%d (%d ??? %d)\n", result, n, r);
	printf("r=%d\n", r);

	int i;
	for (i = 0; i < r; i++) {
		printf("%d ", u[i]);
	}
	printf("\n");
}

int new_mapping(int n, int linesCount) {
	int finalSize = 0;
	int finalCursor = 0;
	int i, j;
	printf("LinesCount =%d\n", linesCount);
	for (i = 0; i < linesCount; i++) {
		printf("i=%d\n", i);
		int findMatch = 0;

		for (j = 0; j < finalSize; j++) {
			int *u = malloc(sizeof(int) * 10);
			int *u_size;
			int r = bucket_union_array(data[i], dataSize[i], dataFinal[j],
					dataFinalSize[j], u, &u_size);
			int result = (r <= n);
			printf("Union =%d (%d ?=>? %d)\n", result, n, r);

			if (r <= n) {
				int z;
				for (z = 0; z < u_size; z++) {
					dataFinal[j][z] = u[z];
				}
				dataFinalSize[j] = u_size;

				findMatch = 1;
				break;
			}
		}
		if (!findMatch) {
			//Create new bucket
			int z;
			for (z = 0; z < dataSize[i]; z++) {
				dataFinal[finalCursor][z] = data[i][z];
			}
			dataFinalSize[finalCursor] = dataSize[i];

			finalSize++;
			finalCursor++;
			printf("BucketSize = %d\n", finalCursor);
		}
		printf("\n");
		printFinalData();
	}
	printf("Final Result:\n");
	return finalCursor;
}

void printSourceData() {
	printf("Source data:\n");
	int i, j;
	for (i = 0; i < MAX_SIZE; i++) {
		for (j = 0; j < dataSize[i]; j++) {
			printf("%d ", data[i][j]);
		}
		if (j > 0)
			printf("\n");
	}
	printf("=======\n");
}

void printFinalData() {
	printf("Final data:\n");
	int i, j;
	for (i = 0; i < MAX_SIZE; i++) {
		for (j = 0; j < dataFinalSize[i]; j++) {
			printf("%d ", dataFinal[i][j]);
		}

		if (j > 0)
			printf("\n");
	}
	printf("=======\n");
}

int main(int argc, char **argv) {
	setvbuf(stdout, NULL, _IONBF, 0);
	char* fileName = "buckets_sample.in";

	//puts("start1");
	//int lines = scan_number_of_lines(fileName);
	//printf("Lines = %d\n", lines);
	//puts("finished1");
	puts("start2");
	readFromFile(fileName);
	printSourceData();
	printFinalData();
	puts("finished2");
	puts("start3");
	new_mapping(4, 9);
	puts("finished3");
	printSourceData();
	printFinalData();
	return 0;
}

