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
	//printf("SORT");
	bucket_type f = *((bucket_type*) elem1);
	bucket_type s = *((bucket_type*) elem2);
	//printf("#%d {%d} -- #%d {%d}\n", f.old_index, f.size, s.old_index, s.size);
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

void printBuckets(int n, bucket_type buckets[10]) {
	/*
	 * Print the data in 'array'.
	 */
	int j, k;
	for (j = 0; j < n; ++j) {
		printf("bucket (# %d) {%d} :", buckets[j].old_index, buckets[j].size);
		for (k = 0; k < buckets[j].size; ++k) {
			printf("%4d ", buckets[j].id[k]);
		}
		putchar('\n');
	}
}

void printSingleBucket(bucket_type b) {
	int k;
	printf("bucket (# %d) {%d} :", b.old_index, b.size);
	for (k = 0; k < b.size; ++k) {
		printf("%4d ", b.id[k]);
	}
	putchar('\n');
}

int loadBucketsFromFile(bucket_type buckets[10]) {

	char* filename = "buckets_sample.in";
	int i;
	/*
	 * Open the file.
	 */
	FILE *file = fopen(filename, "r");
	if (file) {
		//int array[10][10];
		//int size[10];
		int j, k;
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

		putchar('\n');

		printBuckets(i, buckets);
		//Sort
		printf("SORTING BY SIZE\n");
		qsort(buckets, i, sizeof(bucket_type), compareBuckets);
		printBuckets(i, buckets);

	} else /* fopen() returned NULL */
	{
		perror(filename);
	}

	return i;
	//readFromFile(filename, 10);
}

int BUCKET_SIZE = 10;

bucket_type bucket_union_struct(bucket_type in1, bucket_type in2) {
	bucket_type r;
	int bucket_size = 0;
	//int bucket_union[BUCKET_SIZE];
	int *bucket_union = calloc(10, sizeof(int));
	int i, j;

	for (i = 0; i < in1.size; i++) {
		printf("%d ", in1.id[i]);
	}
	printf(" --+-- ");
	for (i = 0; i < in2.size; i++) {
		printf("%d ", in2.id[i]);
	}
	printf("  ===  ");

	for (i = 0; i < in1.size; i++) {
		bucket_union[i] = in1.id[i];
		bucket_size++;
	}

	for (i = 0; i < in2.size; i++) {
		int contain = 0;
		for (j = 0; j < bucket_size; j++) {
			if (in2.id[i] == bucket_union[j]) {
				contain++;
			}
		}
		if (contain == 0) {
			bucket_union[bucket_size] = in2.id[i];
			bucket_size++;
		}
	}

	for (i = 0; i < bucket_size; i++) {
		//b[i] = bucket_union[i];
		printf("%d ", bucket_union[i]);
	}
	printf("\n");

	//bucket.values = bucket_union;

	r.id = bucket_union;
	r.size = bucket_size;
	//printf("Size :%d\n", r.size);
	//for (i = 0; i < bucket_size; i++) {
	//	printf("%d ", r.id[i]);
	//}
	//printf("\n");

	return r;
}

int combine(int n, bucket_type buckets[10], bucket_type out_buckets[10],
		int *out_bucket_size, int bucket_index[n]) {

	int i, k;
	int pos = 0;
	for (i = 0; i < n; i++) {
		bucket_type b = buckets[i];
		//printf("#%d  ", b.old_index);

		int fit = 0;

		for (k = 0; k < pos; k++) {
			bucket_type r = bucket_union_struct(buckets[i], out_buckets[k]);
			r.old_index = -1;
			printSingleBucket(r);

			if (r.size <= 4) {
				printf("FIT %d-->%d\n", i, pos);
				int z;
				for (z = 0; z < out_buckets[k].size; z++) {
					printf("%d ", out_buckets[k].id[z]);
				}
				printf(" --->  ");
				for (z = 0; z < r.size; z++) {
					printf("%d ", r.id[z]);
				}
				printf("\n");
				//out_buckets[pos].old_index = pos;
				out_buckets[k].id = r.id;
				out_buckets[k].size = r.size;
				fit = 1;

				bucket_index[i] = k;

				break;
			}
		}
		//bucket_type r = bucket_union_struct(buckets[i], out_buckets[0]);
		if (!fit) {
			out_buckets[pos].size = buckets[i].size;
			out_buckets[pos].old_index = pos;
			out_buckets[pos].id = buckets[i].id;
			printf("NEW %d-->%d\n", i, pos);
			bucket_index[i] = pos;
			pos++;
		}

		printBuckets(pos, out_buckets);
		printf("\n");
	}

	printf("\nOUT BUCKETS:\n");
	printBuckets(pos, out_buckets);

	printf("\nBUCKET MAPPING:\n");
	for (i = 0; i < n; i++) {
		printf("%d --> %d\n", i, bucket_index[i]);
	}

	*out_bucket_size = pos;
	return pos;
}

void mainLoad(char** args) {
	//mainFinal(args);
	int i = 10;
	int j = 10;
	bucket_type buckets[10];
	int n = loadBucketsFromFile(&buckets);

	bucket_type out_buckets[10];
	int bucket_index[n];
	int out_bucket_sizeP;
	int out_bucket_size = combine(n, &buckets, &out_buckets, &out_bucket_sizeP,
			&bucket_index);

	printf("\nOUT BUCKETS:\n");

	printBuckets(out_bucket_sizeP, out_buckets);

	printf("\nBUCKET MAPPING:\n");
	for (i = 0; i < n; i++) {
		printf("%d --> %d\n", i, bucket_index[i]);
	}



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

void mainCombineTest() {
	bucket_type in1;
	bucket_type in2;

	in1.size = 3;
	in1.old_index = 1;
	int a1[3] = { 1, 2, 3 };
	in1.id = a1;

	in2.size = 3;
	in2.old_index = 1;
	int a2[3] = { 3, 4, 5 };
	in2.id = a2;

	bucket_type r = bucket_union_struct(in1, in2);
	int size = r.size;
	printf("Size :%d\n", size);
	printf("Size :%d\n", r.size);
	int i;
	for (i = 0; i < r.size; i++) {
		printf("%d ", r.id[i]);
	}
}

void main(char** args) {
	setvbuf(stdout, NULL, _IONBF, 0);
	mainLoad(args);
	//mainCombineTest();
}
