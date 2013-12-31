/*
 * hw8.c
 *
 *  Created on: Dec 31, 2013
 *      Author: Administrator
 */
#include <stdio.h>
#include "iputil.h"

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

struct prefix readFile(char* fileName, int *lc) {
	struct prefix list;
	FILE *fr;
	fr = fopen(fileName, "rt");
	if (fr == 0) {
		return list;
	}
	char line[280];

	int lineCount = 0;
	/* get a line, up to 80 chars from fr.  done if NULL */
	while (fgets(line, 280, fr) != NULL) {
		lineCount++;
		char* lineIn = line;
		struct prefix p = parseIpFromChar(lineIn);
		printStructPrefix(p);

		if (list.ip == 0 && list.len == 0){
			list = p;
		}else{
			list.next = &p;
		}
	}

	fclose(fr);
	*lc = lineCount;
	return list;
}

void testParse() {

	struct prefix p1;
	p1.ip = 12345;
	p1.len = 8;
	printStructPrefix(p1);

	char* line2 = "1.2.3.4/16";
	struct prefix p2 = parseIpFromChar(line2);
	printStructPrefix(p2);

	char* line3 = "20.30.40.0";
	struct prefix p3 = parseIpFromChar(line3);
	printStructPrefix(p3);

	char* line4 = "255.255.255.255";
	struct prefix p4 = parseIpFromChar(line4);
	printStructPrefix(p4);
}

void testRead() {
	char* fileName = "test.in";
	int lineCount = 0;
	struct prefix list = readFile(fileName, &lineCount);

	printf("File: %s :%d\n", fileName, lineCount);

	printStructPrefixList(0, list);
}

int main(int argc, const char* argv[]) {
	setvbuf(stdout, NULL, _IONBF, 0);
	//testParse();
	testRead();
	printf("Finished\n");
	return 0;
}
