/*
 * hw8.c
 *
 *  Created on: Dec 31, 2013
 *      Author: Administrator
 */
#include <stdio.h>
#include <stdlib.h>
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

struct prefix* readFile(char* fileName, int *lc) {
	struct prefix *list = (struct prefix*) malloc(sizeof(struct prefix));
	list->ip = 0;
	list->len = 0;
	list->next = NULL;

	FILE *fr;
	fr = fopen(fileName, "rt");
	if (fr == 0) {
		return NULL;
	}
	char line[80];

	int lineCount = 0;
	/* get a line, up to 80 chars from fr.  done if NULL */
	struct prefix *curr;
	curr = list;
	while (fgets(line, 80, fr) != NULL) {
		lineCount++;
		char* lineIn = line;

		struct prefix *p = parseIpFromChar(lineIn);
		printStructPrefix(*p);

		if (curr->ip == 0 && curr->len == 0 && curr->next == NULL) {
			curr->ip = p->ip;
			curr->len = p->len;
		} else {
			curr->next = p;
			curr = p;
		}
	}

	fclose(fr);
	*lc = lineCount;
	return list;
}

int delete(unsigned int ip, unsigned char len, struct prefix *list) {

	struct prefix *curr = list;
	struct prefix *prev = NULL;
	int found;

	printf("\nDeleting [%u / %u] \n", ip, len);

	while (curr != NULL) {
		if (curr->ip == ip && curr->len == len) {
			found = 1;
			break;
		} else {
			prev = curr;
			curr = curr->next;
		}
	}
	if (found) {
		//TODO - decide if it's first, last or in middle
		if (prev == NULL) {
			list = list->next;
		} else if (curr->next == NULL) {
			prev->next = NULL;
			free(curr);
		} else {
			prev->next = curr->next;
			free(curr);
		}
		printf("DELETED!\n");
	} else {
		printf("NOTHING!\n");
	}

	return found;
}

int search(unsigned int ip, unsigned char len, struct prefix *list) {

	struct prefix *curr = list;
	int found = 0;

	printf("\nSearching the list for value [%u / %u] \n", ip, len);

	while (curr != NULL) {
		if (curr->ip == ip && curr->len == len) {
			found = 1;
			break;
		} else {
			curr = curr->next;
		}
	}

	if (found) {
		printf("FOUND!\n");
		return 1;
	} else {
		printf("NOTHING!\n");
		return NULL;
	}
	return 0;
}

void testParse() {

	struct prefix p1;
	p1.ip = 12345;
	p1.len = 8;
	printStructPrefix(p1);

	char* line2 = "1.2.3.4/16";
	struct prefix *p2 = parseIpFromChar(line2);
	printStructPrefix(*p2);

	char* line3 = "20.30.40.0";
	struct prefix *p3 = parseIpFromChar(line3);
	printStructPrefix(*p3);

	char* line4 = "255.255.255.255";
	struct prefix *p4 = parseIpFromChar(line4);
	printStructPrefix(*p4);
}

void testRead() {
	//char* fileName = "inserted_prefixes";
	//char* fileName = "routing_table";
	char* fileName = "test.in";
	int lineCount = 0;
	struct prefix *list = readFile(fileName, &lineCount);

	printf("File: %s :%d\n", fileName, lineCount);

	printStructPrefixList(0, list);

	search(927091968, 24, list);
	search(123, 24, list);

	//printf(">>%d\n", list->len);

	printStructPrefixList(0, list);

	//delete(927091968, 24, list);
	delete(16909060, 32, list);

	printStructPrefixList(0, list);
}

void testList() {
	struct prefix *list = (struct prefix*) malloc(sizeof(struct prefix));

	list->ip = 16909060;
	list->len = 32;

	struct prefix *new1 = (struct prefix*) malloc(sizeof(struct prefix));

	list->next = new1;
	new1->ip = 169090600;
	new1->len = 32;

	struct prefix *new2 = (struct prefix*) malloc(sizeof(struct prefix));

	new1->next = new2;
	new2->ip = 927091968;
	new2->len = 24;

	struct prefix *new3 = (struct prefix*) malloc(sizeof(struct prefix));

	new2->next = new3;
	new3->ip = 167168;
	new3->len = 16;

	printStructPrefixList(0, list);

}
int main(int argc, const char* argv[]) {
	setvbuf(stdout, NULL, _IONBF, 0);
	//testParse();
	testRead();
	//testList();
	printf("Finished\n");
	return 0;
}
