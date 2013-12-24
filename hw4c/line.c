#include<stdio.h>
/*DECLARATIONS*/

//typedef struct Bucket {
//	int size;
//	int values[18];
//};
int main(int argc, char **argv) {
	setvbuf(stdout, NULL, _IONBF, 0);

	char* fileName = "buckets_sample.in";

	puts("start1");
	FILE *fr;
	fr = fopen(fileName, "rt");
	if (fr == NULL)
		perror("Error opening file");
	int c; /* Nb. int (not char) for the EOF */
	unsigned long lineCount = 0;

	while (c = fgetc(fr), !feof(fr)) {
		if (c == '\n')
			lineCount++;
	}

	printf("%lu newline characters\n", lineCount);
	fclose(fr);
	puts("finished1");

	puts("start2");
	fr = fopen(fileName, "rt");
	if (fr == NULL)
		perror("Error opening file");

	int linePos = 0;
//	char line[280];
	char* line = malloc(sizeof(char)*280);

	/* get a line, up to 80 chars from fr.  done if NULL */
	while (fgets(line, 280, fr) != NULL) {

		int fieldPos = 0;
		char* pch;

		printf("%d\t", linePos);

		printf(&line);



		pch = strtok(line, " ");
		while (pch != NULL) {
			printf("Tok%d >%s\t", fieldPos, pch);
			pch = strtok(NULL, " ");
			fieldPos++;
		}

		//bucketStruct[linePos].size = fieldPos;
		//printf("\t(%d)\n", bucketStruct[linePos].size);
		linePos++;
		//maxBucketSize = max(maxBucketSize, fieldPos);

		printf("\n");
	}

	//printf("Max bucket size = %d\n", maxBucketSize);
	fclose(fr);
	printf("finished2");
	return 0;
}
