#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int old_index;
	int size;
	int *id;
} bucket_type;

int comp(const void * elem1, const void * elem2) {
	int f = *((int*) elem1);
	int s = *((int*) elem2);
	if (f > s)
		return 1;
	if (f < s)
		return -1;
	return 0;
}
int sortTest(int argc, char* argv[]) {
	int x[] = { 4, 5, 2, 3, 1, 0, 9, 8, 6, 7 };

	qsort(x, sizeof(x) / sizeof(*x), sizeof(*x), comp);

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

	int old_indices_array[3] = {3,7,11};

	printf("how many original buckets are contained in new bucket: %d\n",contain);
	printf("all the old indices stored in that new bucket:\n");

	int size = sizeof(old_indices_array) / sizeof(int);
	int i;
	for (i=0;i<size;i++){
		printf("%d\n",old_indices_array[i]);
	}
}

void main(char** args) {
	setvbuf(stdout, NULL, _IONBF, 0);

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
