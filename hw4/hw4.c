#include<stdio.h>
/*DECLARATIONS*/
typedef struct Bucket {
	int size;
	int values[20];
};
/* note semi-colon here */
/*DEFINITIONS*/

void show_union(int a[10], int b[10], int m, int n) {
	int c[20], i, j, k = 0, flag = 0;
	for (i = 0; i < m; i++) {
		c[k] = a[i];
		k++;
	}
	for (i = 0; i < n; i++) {
		flag = 0;
		for (j = 0; j < m; j++) {
			if (b[i] == c[j]) {
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			c[k] = b[i];
			k++;
		}
	}
	printf("\nElement of resultant set\n\n");
	for (i = 0; i < k; i++) {
		printf("\t%d", c[i]);
	}
}

struct Bucket bucket_union_struct(int n, int bucket_a[n], int size_a,
		int bucket_b[n], int size_b) {

	struct Bucket bucket_union;
	//int bucket_union[n];
	//int bucket_size = size_a;

	int i, j, k;
	int emptyFrom = 0;

	for (i = 0; i < size_a; i++) {
		printf("%d ", bucket_a[i]);
	}
	printf("\n");
	for (i = 0; i < size_b; i++) {
		printf("%d ", bucket_b[i]);
	}
	printf("\n");

	for (i = 0; i < size_a; i++) {
		bucket_union.values[i] = bucket_a[i];
	}

	for (i = 0; i < size_b; i++) {

		int contain = 0;
		for (j = 0; j < bucket_union.size; j++) {
			if (bucket_b[i] == bucket_union.values[j]) {
				contain++;
			}
		}
		if (contain == 0) {
			bucket_union.values[bucket_union.size] = bucket_b[i];
			bucket_union.size++;

		}
	}

	for (i = 0; i < bucket_union.size; i++) {
		printf("%d ", bucket_union.values[i]);
	}
	printf("\n");
	return bucket_union;
}

struct Bucket bucket_union_struct2(int n, int bucket_a[n], int size_a,
		int bucket_b[n], int size_b) {

	struct Bucket bucket;

	int bucket_union[n];
	int bucket_size = size_a;

	int i, j, k;
	int emptyFrom = 0;

	for (i = 0; i < size_a; i++) {
		printf("%d ", bucket_a[i]);
	}
	printf("\n");
	for (i = 0; i < size_b; i++) {
		printf("%d ", bucket_b[i]);
	}
	printf("\n");

	for (i = 0; i < size_a; i++) {
		bucket_union[i] = bucket_a[i];
	}

	for (i = 0; i < size_b; i++) {

		int contain = 0;
		for (j = 0; j < bucket_size; j++) {
			if (bucket_b[i] == bucket_union[j]) {
				contain++;
			}
		}
		if (contain == 0) {
			bucket_union[bucket_size] = bucket_b[i];
			bucket_size++;

		}
	}

	for (i = 0; i < bucket_size; i++) {
		bucket.values[i] = bucket_union[i];
		printf("%d ", bucket_union[i]);
	}

	//bucket.values = bucket_union;
	bucket.size = bucket_size;
	return bucket;
}

int* bucket_union(int n, int bucket_a[n], int size_a, int bucket_b[n],
		int size_b) {

	int bucket_union[n];
	int bucket_size = size_a;

	int i, j, k;
	int emptyFrom = 0;

	for (i = 0; i < size_a; i++) {
		printf("%d ", bucket_a[i]);
	}
	printf("\n");
	for (i = 0; i < size_b; i++) {
		printf("%d ", bucket_b[i]);
	}
	printf("\n");

	for (i = 0; i < size_a; i++) {
		bucket_union[i] = bucket_a[i];
	}

	for (i = 0; i < size_b; i++) {

		int contain = 0;
		for (j = 0; j < bucket_size; j++) {
			if (bucket_b[i] == bucket_union[j]) {
				contain++;
			}
		}
		if (contain == 0) {
			bucket_union[bucket_size] = bucket_b[i];
			bucket_size++;

		}
	}

	for (i = 0; i < bucket_size; i++) {
		printf("%d ", bucket_union[i]);
	}

	return bucket_union;
}

int new_mapping() {
	return 0;
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

//Print result to file
void fprint_result(int l, int linePos, int buckets[l][l], int bucketsSize[]) {
	FILE * fout;
	fout = fopen("buckets.out", "w+");

	int i, j;
	for (i = 0; i < linePos; i++) {
		for (j = 0; j < bucketsSize[i]; j++) {
			fprintf(fout, "%d ", buckets[i][j]);
		}
		fprintf(fout, "\n");
	}

	fprintf(fout, "\n");
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

int scan_number_of_lines(FILE *fr) {
	char line[280];

	int lineCount = 0;
	/* get a line, up to 80 chars from fr.  done if NULL */
	while (fgets(line, 280, fr) != NULL) {
		lineCount++;
	}
	fclose(fr);

	return lineCount;
}
struct Bucket b;

int main(int argc, char **argv) {
	setvbuf(stdout, NULL, _IONBF, 0);
	int n = 4;
	int size_a = 2;
	int size_b = 2;
	int bucket_a[] = { 1, 2, 0, 0 };
	int bucket_b[] = { 2, 4, 0, 0 };

	b = bucket_union_struct2(n, bucket_a, size_a, bucket_b, size_b);
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

int mainOld(int argc, char **argv) {
	setvbuf(stdout, NULL, _IONBF, 0);
	FILE *fr;

	puts("start");
	fr = fopen("buckets.in", "rt");
	//fr = fopen("buckets_sample.in", "rt");
	int l = scan_number_of_lines(fr);
	printf("Lines = %d\n", l);

	//fr = fopen("buckets_sample.in", "rt");
	fr = fopen("buckets.in", "rt");
	int buckets[l][20];
	int bucketsSize[l];
	int bucketsMapping[l];

	int linePos = 0;
	char line[280];

	puts("start2");

	/* get a line, up to 80 chars from fr.  done if NULL */
	while (fgets(line, 280, fr) != NULL) {

		int fieldPos = 0;

		char* pch;

		printf("%d\t", linePos);
		pch = strtok(line, " ");
		while (pch != NULL) {
			int value;
			sscanf(pch, "%d", &value);

			buckets[linePos][fieldPos] = value;

			printf("%d ", value);
			pch = strtok(NULL, " ");
			fieldPos++;
		}

		bucketsSize[linePos] = fieldPos;
		printf("\t(%d)\n", bucketsSize[linePos]);
		linePos++;
	}

	puts("finished2");

	fclose(fr); /* close the file prior to exiting the routine */

	print_result(l, linePos, buckets, bucketsSize);
	return 0;
}

int mainStruct(int argc, char **argv) {
	setvbuf(stdout, NULL, _IONBF, 0);
	FILE *fr;

	puts("start");
	fr = fopen("buckets.in", "rt");
	//fr = fopen("buckets_sample.in", "rt");
	int l = scan_number_of_lines(fr);
	printf("Lines = %d\n", l);

	//fr = fopen("buckets_sample.in", "rt");
	fr = fopen("buckets.in", "rt");
	int bucketsMapping[l];
	struct Bucket bucketStruct[l];

	int linePos = 0;
	char line[280];

	puts("start2");

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
	}

	puts("finished2");

	fclose(fr); /* close the file prior to exiting the routine */

	//print_result(l, linePos, buckets, bucketsSize);
	return 0;
}

