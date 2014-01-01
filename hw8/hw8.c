/*
 * hw8.c
 *
 *  Created on: Dec 31, 2013
 *      Author: Administrator
 */
#include <stdio.h>
#include <stdlib.h>
#include "iputil.h"

int insertCounter = 0;
int insertFrequency[100000] = { 0 };
int searchCounter = 0;
int removeCounter = 0;
int removeFrequency[100000] = { 0 };

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

struct prefix* input(char* fileName, int *lc) {
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

struct prefix* addSorted(unsigned int ip, unsigned char len,
		struct prefix *list) {
	struct prefix *curr = list;
	struct prefix *prev = NULL;
	printf("Adding [%u / %u] \n", ip, len);

	insertCounter = 0;
	while (curr != NULL) {
		insertCounter++;
		if (curr->ip > ip) {
			break;
		} else {
			prev = curr;
			curr = curr->next;
		}
	}
	insertFrequency[insertCounter]++;
	struct prefix *new = (struct prefix*) malloc(sizeof(struct prefix));
	new->ip = ip;
	new->len = len;
	new->next = NULL;

	printf("%d\t", insertCounter);
	//TODO - decide if it's first, last or in middle
	if (list == NULL || (list->ip == 0 && list->len == 0)) {
		list = new;
		printf("ADDED NEW LIST!\n");
	} else if (prev == NULL) {
		new->next = list;
		list = new;
		printf("ADDED FIRST!\n");
	} else if (prev->next == NULL) {
		prev->next = new;
		printf("ADDED LAST!\n");
	} else {
		new->next = curr;
		prev->next = new;
		printf("ADDED MIDDLE!\n");
	}

	return list;
}

//struct prefix* addSortedByPrefix(struct prefix *new, struct prefix *list) {
//	struct prefix *curr = list;
//	struct prefix *prev = NULL;
//	printf("Adding [%u / %u] \n", new->ip, new->len);
//
//	while (curr != NULL) {
//		if (curr->ip > new->ip) {
//			break;
//		} else {
//			prev = curr;
//			curr = curr->next;
//		}
//	}
//	//new->next = NULL;
//
//	//TODO - decide if it's first, last or in middle
//	if (list == NULL || (list->ip == 0 && list->len == 0)) {
//		list = new;
//		printf("ADDED NEW LIST!\n");
//	} else if (prev == NULL) {
//		new->next = list;
//		list = new;
//		printf("ADDED FIRST!\n");
//	} else if (prev->next == NULL) {
//		prev->next = new;
//		printf("ADDED LAST!\n");
//	} else {
//		new->next = curr;
//		prev->next = new;
//		printf("ADDED MIDDLE!\n");
//	}
//
//	return list;
//}

struct prefix* delete(unsigned int ip, unsigned char len, struct prefix *list) {

	struct prefix *curr = list;
	struct prefix *prev = NULL;
	int found = 0;

	printf("\nDeleting [%u / %u] \t", ip, len);
	removeCounter = 0;
	while (curr != NULL) {
		removeCounter++;
		if (curr->ip == ip && curr->len == len) {
			found = 1;
			break;
		} else {
			prev = curr;
			curr = curr->next;
		}
	}

	if (found) {
		removeFrequency[removeCounter]++;
		//TODO - decide if it's first, last or in middle
		if (prev == NULL) {
			//todo free
			//free(list);
			list = list->next;
		} else if (curr->next == NULL) {
			prev->next = NULL;
			free(curr);
		} else {
			prev->next = curr->next;
			free(curr);
		}
		printf("DELETED! %d\n", removeCounter);
	} else {
		printf("NOTHING!\n");
	}

	return list;
}

struct prefix* search(unsigned int ip, unsigned char len, struct prefix *list) {

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
		return curr;
	} else {
		printf("NOTHING!\n");
		return NULL;
	}
}

void length_distribution(struct prefix *list, unsigned int distribution[33]) {

	struct prefix *curr = list;
	printf("\nCalculating Prefix Length Distribution\n");

	while (curr != NULL) {
		distribution[curr->len]++;
		curr = curr->next;
	}

	int i;
	printf("\n====\n");
	for (i = 0; i < 33; i++) {
		printf("%u\t%5u\n", i, distribution[i]);
	}
	printf("====\n");
	for (i = 0; i < 33; i++) {
		printf("%5u ", i);
	}
	printf("\n");
	for (i = 0; i < 33; i++) {
		printf("%5u ", distribution[i]);
	}
	printf("\n");
}

void segment(int d, struct prefix *list) {

	unsigned int groupNumber = power2(d);
	int *groupsCount = calloc(groupNumber, sizeof(int));
	struct prefix *groupTooShort = calloc(1, sizeof(struct prefix));
	//groupTooShort = NULL;

	struct prefix *groups[groupNumber];
	int i;
	for (i = 0; i < groupNumber; i++) {
		groups[i] = calloc(groupNumber, sizeof(struct prefix*));
	}

	int tooShortGroup = 0;

	printf("\nCalculating Prefix Groups [2^%d -> %d]\n", d, groupNumber);

	struct prefix *curr = list;
	while (curr != NULL) {
		unsigned int group = 0;

		printBits(sizeof(curr->ip), &(curr->ip));
		if (curr->len < d) {
			tooShortGroup++;
			groupTooShort = addSorted(curr->ip, curr->len, groupTooShort);
			printf("%u / %u -> tooShortGroup\n", curr->ip, curr->len);
		} else {
			group = (curr->ip >> (32 - d));
			printBits(sizeof(group), &group);
			printf("%u / %u -> %d\n", curr->ip, curr->len, group);
			groupsCount[group]++;
			groups[group] = addSorted(curr->ip, curr->len, groups[group]);
			//groups[group] = addSortedByPrefix(curr, groups[group]);
		}
		curr = curr->next;
	}

	printf("\n====\n");
	printf("SHORT\t%5u\n", tooShortGroup);
	for (i = 0; i < groupNumber; i++) {
		printf("%u\t%5u\n", i, groupsCount[i]);
	}

	printf("\n==SHORT==\n");
	printStructPrefixList(groupTooShort);
	for (i = 0; i < groupNumber; i++) {
		printf("\n== %d ==\n", i);
		printStructPrefixList(groups[i]);
	}
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
	struct prefix *list = input(fileName, &lineCount);

	printf("File: %s :%d\n", fileName, lineCount);

	printStructPrefixList(list);

	search(927091968, 24, list);
	search(123, 24, list);

//printf(">>%d\n", list->len);

	printStructPrefixList(list);

//delete(927091968, 24, list);
	list = delete(16909060, 32, list);

	printStructPrefixList(list);

	list = addSorted(16909060, 30, list);
	list = addSorted(16909061, 31, list);
	list = addSorted(169090601, 32, list);
	list = addSorted(927091969, 8, list);

	printStructPrefixList(list);
	//list = delete(16909060, 32, list);

	unsigned int* distribution = calloc(33, sizeof(unsigned int));
	length_distribution(list, distribution);

	segment(2, list);
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

	printStructPrefixList(list);

}

void printSummary() {
	printf("==== SUMMARY ====\n");

	int i;
	for (i = 0; i < 5000; i++) {
		printf("%d\t%d\t%d\n", i, insertFrequency[i], removeFrequency[i]);
	}
	printf("Insert:\t%d\n", insertCounter);
	printf("Search:\t%d\n", searchCounter);
	printf("Remove:\t%d\n", removeCounter);
}

void run() {
	char* routingName = "routing_table";
	char* insertName = "inserted_prefixes";
	char* removeName = "routing_table";

	int lineCount = 0;
	struct prefix *routingList = input(routingName, &lineCount);
	struct prefix *insertList = input(insertName, &lineCount);
	struct prefix *removeList = input(removeName, &lineCount);

	printStructPrefixList(routingList);

//	struct prefix *curr = insertList;
//	while (curr != NULL) {
//		routingList = addSorted(curr->ip, curr->len, routingList);
//		curr = curr->next;
//	}

	//printStructPrefixList(0, routingList);

//	curr = removeList;
//	while (curr != NULL) {
//		routingList = delete(curr->ip, curr->len, routingList);
//		curr = curr->next;
//	}
//
//	printStructPrefixList(0, routingList);

	//printSummary();
}
int main(int argc, const char* argv[]) {
	setvbuf(stdout, NULL, _IONBF, 0);
//testParse();
	//testRead();
//testList();
	run();
	printf("Finished\n");
	return 0;
}
