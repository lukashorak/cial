#include<stdio.h>
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
	int values[18];
};

int** make2dArray(int rows, int cols) {
	int **x, i;

	MALLOC(x, rows * sizeof(*x));

	for (i = 0; i < rows; i++) {
		MALLOC(x[i], cols * sizeof(**x));
	}
	return x;
}
int** make2dArrayZero(int rows, int cols) {
	int **x, i;

	CALLOC(x, rows, rows * sizeof(*x));

	for (i = 0; i < rows; i++) {
		CALLOC(x[i], cols, cols * sizeof(**x));
	}
	return x;
}

int main(int argc, char **argv) {
	setvbuf(stdout, NULL, _IONBF, 0);

	char* fileName = "buckets_sample.in";

	int **array2d = make2dArray(14000, 30);

	//int i, j;
	//for (i = 0; i < 5; i++) {
	//	for (j = 0; j < 10; j++) {
	//		printf("%d ", array2d[i][j]);
	//	}
	//	printf("\n");
	//}
	//char* fileName = "buckets.in";

	puts("start1");
	//int l = scan_number_of_lines(fileName);
	//printf("Lines = %d\n", l);
	puts("finished1");

	//puts("start2");
	//int maxBucketSize;
	//int bucketsMapping[l];
	//struct Bucket bucketStruct[l];
	//readFromFile(fileName, l, bucketStruct, maxBucketSize);
	//int n = input_bucket_size(maxBucketSize);
	//puts("finished2");

	//puts("start3");
	//struct Bucket finalStruct[l];
	//int finalSize = new_mapping(n, l, &bucketStruct, &finalStruct);
	//puts("finished3");

	//puts("start4");
	//print_result_bucket(l, bucketStruct);
	//print_result_bucket(finalSize, finalStruct);
	//puts("finished4");
	return 0;
}
