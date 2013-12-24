#include<stdio.h>
#include<stdlib.h>
#include <string.h>

/*DECLARATIONS*/
#define MALLOC(p,s)\
if (!((p) = malloc(s))) {\
	fprintf(stderr, "Insufficient memory");\
	exit(1);\
}

#define CALLOC(p,n,s)\
if (!((p) = calloc(n,s))) {\
	fprintf(stderr, "Insufficient memory");\
	exit(1);\
}
typedef struct Bucket {
	int size;
	int values[10];
};

int min(int a, int b);
int max(int a, int b);
int bucket_union_struct4(int n, struct Bucket a, struct Bucket b,
		struct Bucket* bucket);
void print_result(int l, int linePos, int buckets[l][l], int bucketsSize[]);
void print_result_bucket(int linePos, struct Bucket* b);
void fprint_result(int linePos, struct Bucket* b);
int input_bucket_size(int maxBucket);
void readFromFile(char* fileName, struct Bucket* bucketStruct,
		int maxBucketSize);
/* note semi-colon here */
/*DEFINITIONS*/

int bucket_union_struct4(int n, struct Bucket a, struct Bucket b,
		struct Bucket* bucket) {

	int bucket_union[n];
	int bucket_size = a.size;

	int i, j, k;
	int emptyFrom = 0;

	for (i = 0; i < a.size; i++) {
		printf("%d ", a.values[i]);
	}
	printf(" --+-- ");
	for (i = 0; i < b.size; i++) {
		printf("%d ", b.values[i]);
	}
	printf("  ===  ");

	for (i = 0; i < a.size; i++) {
		bucket_union[i] = a.values[i];
	}

	for (i = 0; i < b.size; i++) {

		int contain = 0;
		for (j = 0; j < bucket_size; j++) {
			if (b.values[i] == bucket_union[j]) {
				contain++;
			}
		}
		if (contain == 0) {
			bucket_union[bucket_size] = b.values[i];
			bucket_size++;

		}
	}

	for (i = 0; i < bucket_size; i++) {
		(*bucket).values[i] = bucket_union[i];
		printf("%d ", bucket_union[i]);
	}
	printf("\n");
	//bucket.values = bucket_union;
	(*bucket).size = bucket_size;
	int result = ((*bucket).size <= n);
	printf("Result=%d (%d ??? %d)\n", result, n, (*bucket).size);
	return result;
}

//int l - size of the array
//int linePos - number of real lines
//int buckets[n][n] - data
//int bucketSize[n] - number of values on each line
void print_result(int l, int linePos, int buckets[l][l], int bucketsSize[]) {
	int i, j;
	for (i = 0; i < linePos; i++) {
		for (j = 0; j < bucketsSize[i]; j++) {
			printf("%d ", buckets[i][j]);
		}
		printf("\n");
	}
}

void print_result_bucket(int linePos, struct Bucket* b) {
	int i, j;
	for (i = 0; i < linePos; i++) {
		printf("%d\t", i);
		for (j = 0; j < b[i].size; j++) {
			printf("%d ", b[i].values[j]);
		}
		printf("(%d)\n", b[i].size);
	}

	printf("Bucket count=%d\n", linePos);

}

//Print result to file
void fprint_result(int linePos, struct Bucket* b) {
	FILE * fout;
	fout = fopen("buckets.out", "w+");

	int i, j;
	for (i = 0; i < linePos; i++) {
		fprintf(fout, "%d\t", i);
		for (j = 0; j < b[i].size; j++) {
			fprintf(fout, "%d ", b[i].values[j]);
		}
		fprintf(fout, "(%d)\n", b[i].size);
	}
	fprintf(fout, "\n");
	fprintf(fout, "Bucket count=%d\n", linePos);
	fclose(fout);
}

int input_bucket_size(int maxBucket) {

	//Initialize variables
	int n;
	puts(
			"Number of numbers in a bucket (must be at least like the largest bucket):");
	scanf("%d", &n);
	if (n < maxBucket) {
		printf("n is smaller than largest bucket ( %d )", n);
		return -1;
	}

	return n;
}

int scan_number_of_lines(char* fileName) {

	FILE *fr;
	fr = fopen(fileName, "rt");
	if (fr == NULL)
		perror("Error opening file");
	int c; /* Nb. int (not char) for the EOF */
	unsigned long lineCount = 0;

	/* count the newline characters */
	while ((c = fgetc(fr)) != EOF) {
		if (c == '\n')
			lineCount++;
	}

	printf("%lu newline characters\n", lineCount);

	return lineCount;
}

int scan_number_of_lines2(char* fileName) {
	FILE *fr;
	fr = fopen(fileName, "rt");
	char line[280];

	int lineCount = 0;
	/* get a line, up to 80 chars from fr.  done if NULL */
	while (fgets(line, 280, fr) != NULL) {
		lineCount++;
	}
	fclose(fr);

	return lineCount;
}

int mainS(int argc, char **argv) {
	setvbuf(stdout, NULL, _IONBF, 0);
	int n = 4;

	struct Bucket b1;
	struct Bucket b2;
	b1.values[0] = 1;
	b1.values[1] = 2;
	b1.values[2] = 3;
	b1.values[3] = 4;
	b1.size = 4;
	b2.values[0] = 2;
	b2.values[1] = 5;
	b2.size = 2;

	struct Bucket b;
//b = bucket_union_struct3(n, b1, b2, b);
	int r = bucket_union_struct4(n, b1, b2, &b);
//struct Bucket b = bucket_union_struct2(n, bucket_a, size_a, bucket_b,
//		size_b);

	int s = b.size;
	int* ar = b.values;

	printf("\n");
	printf("%d\n", s);
//show_union(bucket_a, bucket_b, 2, 2);
	int i;

	for (i = 0; i < s; i++) {
		printf("%d ", b.values[i]);
	}
	printf("\n");
	for (i = 0; i < s; i++) {
		printf("%d ", ar[i]);
	}
	printf("\n");

	return 0;
}

void readFromFile(char* fileName, struct Bucket* bucketStruct,
		int maxBucketSize) {
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
			bucketStruct[linePos].values[fieldPos] = value;
			printf("%d ", value);
			pch = strtok(NULL, " ");
			fieldPos++;
		}

		bucketStruct[linePos].size = fieldPos;
		printf("\t(%d)\n", bucketStruct[linePos].size);
		linePos++;
		maxBucketSize = max(maxBucketSize, fieldPos);
	}

	printf("Max bucket size = %d\n", maxBucketSize);
	fclose(fr);
}

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

int new_mapping(int n, int l, struct Bucket* bucketStruct,
		struct Bucket* finalStruct) {
	int finalSize = 0;
	int i, j;
	printf("l=%d\n", l);
	for (i = 0; i < l; i++) {
		printf("i=%d\t", i);
		int findMatch = 0;

		//int bestMatch = n;
		//int bestMatchIndex = 0;
		//struct Bucket bestMatchStruct;

		for (j = 0; j < finalSize; j++) {
			printf("%d\t", j);
			struct Bucket newBucket;
			int r = bucket_union_struct4(n, bucketStruct[i], finalStruct[j],
					&newBucket);

			if (r) {
				finalStruct[j] = newBucket;
				findMatch = 1;
				break;
			}
		}
		if (findMatch) {
			//finalStruct[bestMatchIndex] = bestMatchStruct;
		} else {

			struct Bucket newBucket;
			struct Bucket newBucketTmp;
			newBucket.size = 0;
			newBucketTmp.size = 0;

			//newBucketTmp.values;
			//(int n, int bucket_a[n], int size_a,
			//	int bucket_b[n], int size_b)
			int r = bucket_union_struct4(n, bucketStruct[i], newBucketTmp,
					&newBucket);

			finalStruct[finalSize].size = newBucket.size;
			printf("Size :%d --- ", newBucket.size);
			int z;
			for (z = 0; z < newBucket.size; z++) {
				finalStruct[finalSize].values[z] = newBucket.values[z];
				printf("%d ", newBucket.values[z]);
			}
			finalSize++;

			printf("FINAL = %d\n", finalSize);
			//print_result_bucket(finalSize, finalStruct);
		}
		printf("\n");
	}
	//printf("\n");
	printf("Final Result:\n");
	print_result_bucket(finalSize, finalStruct);
	return finalSize;
}

int main(int argc, char **argv) {
	setvbuf(stdout, NULL, _IONBF, 0);

	char* fileName = "buckets_sample.in";
//char* fileName = "buckets.in";

	puts("start1");
	int lines = scan_number_of_lines(fileName);
	int l = lines;
	printf("Lines = %d\n", l);
	puts("finished1");

	puts("start2");
	int maxBucketSize;
	int bucketsMapping[l];
//struct Bucket bucketStruct[l];

	struct Bucket *bucketStruct;
	MALLOC(bucketStruct, l * sizeof(bucketStruct));
	readFromFile(fileName, &bucketStruct, maxBucketSize);
	printf("Lines = %d\n", l);
	int n = input_bucket_size(maxBucketSize);
	int n = 4;
	puts("finished2");

	puts("start3");
//struct Bucket finalStruct[l];
	struct Bucket *finalStruct;
	MALLOC(finalStruct, l * sizeof(finalStruct));
	printf("Lines = %d\n", l);
	int finalSize = new_mapping(n, l, &bucketStruct, &finalStruct);
	puts("finished3");

	puts("start4");
	//print_result_bucket(l, &bucketStruct);
	print_result_bucket(finalSize, &finalStruct);
	fprint_result(finalSize, &finalStruct);
	puts("finished4");
	return 0;
}

