#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#define ARRAYSIZE(x)  (sizeof(x)/sizeof(*(x)))

typedef struct {
	int old_index;
	int size;
	int *id;
} bucket_type;

int compareBuckets(const void * elem1, const void * elem2) {
	printf("SORT");
	bucket_type f = *((bucket_type*) elem1);
	bucket_type s = *((bucket_type*) elem2);
	printf("#%d {%d} -- #%d {%d}\n", f.old_index, f.size, s.old_index, s.size);
	if (f.size > s.size)
		return -1;
	if (f.size < s.size)
		return 1;
	return 0;
}

int sortTest(int argc, char* argv[]) {
	int x[] = { 4, 5, 2, 3, 1, 0, 9, 8, 6, 7 };

	qsort(x, sizeof(x) / sizeof(*x), sizeof(*x), compare_int);

	int i;
	for (i = 0; i < 10; i++) {
		printf("%d ", x[i]);
	}

	return 0;
}

static unsigned int dataSize[99];
static unsigned int data[99][99];

void readFromFile(char* fileName, int maxBucketSize) {
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

void methodA() {
	printf("input a sorted bucket index:");
	int sorted_bucket_index;
	scanf("%d", &sorted_bucket_index);

	int old_index = 5;
	printf("corresponding old index: %d\n", old_index);
}

void methodB() {
	printf("input a old index:");
	int old_index;
	scanf("%d", &old_index);

	int new_index = 2;
	printf("corresponding new bucket index: %d\n", new_index);
}

void methodC() {
	printf("input a new index:");
	int new_index;
	scanf("%d", &new_index);

	int contain = 123;

	int old_indices_array[3] = { 3, 7, 11 };

	printf("how many original buckets are contained in new bucket: %d\n",
			contain);
	printf("all the old indices stored in that new bucket:\n");

	int size = sizeof(old_indices_array) / sizeof(int);
	int i;
	for (i = 0; i < size; i++) {
		printf("%d\n", old_indices_array[i]);
	}
}

void mainFinal(char** args) {

	printf("Select Method as in Readme {A,B,C}:");
	char method;
	scanf("%c", &method);

	switch (method) {
	case 'A':
		printf("A\n");
		methodA();
		break;
	case 'B':
		printf("B\n");
		methodB();
		break;
	case 'C':
		printf("C\n");
		methodC();
		break;
	}

	printf("Finished");
}

void mainLoad(char** args, bucket_type buckets[10]) {

	char* filename = "buckets_sample.in";

	//bucket_type buckets[10];

	/*
	 * Open the file.
	 */
	FILE *file = fopen(filename, "r");
	if (file) {
		//int array[10][10];
		//int size[10];
		int i, j, k;
		char buffer[BUFSIZ];
		char* token;
		char* string;

		/*
		 * Read each line from the file.
		 */
		for (i = 0; fgets(buffer, sizeof buffer, file); ++i, j = 0) {
			string = buffer;
			buckets[i].old_index = i;
			int *linearray = calloc(10, sizeof(int));

			//Fill the Array
			while ((token = strsep(&string, " ")) != NULL) {
				//printf("%s ", token);
				sscanf(token, "%d", &linearray[j]);
				j++;
			}
			buckets[i].id = linearray;
			buckets[i].size = j;
		}
		fclose(file);
		/*
		 * Print the data in 'array'.
		 */
		for (j = 0; j < i; ++j) {
			printf("bucket (# %d) {%d} :", buckets[j].old_index,
					buckets[j].size);
			for (k = 0; k < buckets[j].size; ++k) {
				printf("%4d ", buckets[j].id[k]);
			}
			putchar('\n');
		}

		//Sort

		printf("SORTING BY SIZE\n");

		qsort(buckets, 9, sizeof(bucket_type),
				compareBuckets);
//		qsort(buckets, sizeof(buckets) / sizeof(*buckets), sizeof(*buckets),
//						compareBuckets);

		for (j = 0; j < i; ++j) {
			printf("bucket (# %d) {%d} :", buckets[j].old_index,
					buckets[j].size);
			for (k = 0; k < buckets[j].size; ++k) {
				printf("%4d ", buckets[j].id[k]);
			}
			putchar('\n');
		}

	} else /* fopen() returned NULL */
	{
		perror(filename);
	}

	//readFromFile(filename, 10);
}

void main(char** args) {
	setvbuf(stdout, NULL, _IONBF, 0);

	//mainFinal(args);
	int i = 10;
	int j = 10;
	bucket_type buckets[10];
	mainLoad(args, &buckets);
}
