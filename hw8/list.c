/*
 * list.c
 *
 *  Created on: 2 Jan 2014
 *      Author: Lukas
 */

#include <stdlib.h>
#include <stdio.h>
#include "iputil.h"
#include "list.h"

int insertCounter = 0;
int insertFrequency[100000] = { 0 };
int searchCounter = 0;
int removeCounter = 0;
int removeFrequency[100000] = { 0 };

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

struct prefix* delete(unsigned int ip, unsigned char len, struct prefix *list) {

	struct prefix *curr = list;
	struct prefix *prev = NULL;
	int found = 0;

	printf("Deleting [%u / %u] \t", ip, len);
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
		printf("%d\t", removeCounter);
		//Decide if it's first, last or in middle
		if (curr == NULL) {
			printf("EMPTY!\n");
		} else if (prev == NULL) {
			//FIXME free
			//free(list);
			printf("DELETED HEAD!\n");
			list = list->next;
		} else if (curr->next == NULL) {
			printf("DELETED LAST!\n");
			prev->next = NULL;
			free(curr);
		} else {
			printf("DELETED MIDDLE!\n");
			prev->next = curr->next;
			free(curr);
		}

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

void printSummary() {
	printf("==== SUMMARY ====\n");

	int i;
	int group = 0;
	int size = 1000;
	int insertGroup = 0;
	int removeGroup = 0;
	for (i = 0; i < 35000; i++) {
		//printf("%d\t%d\t%d\n", i, insertFrequency[i], removeFrequency[i]);
		group = i / size;
		insertGroup += insertFrequency[i];
		removeGroup += removeFrequency[i];
		if (i % size == 0) {
			printf("%d\t%d\t%d\n", group, insertGroup, removeGroup);
			insertGroup = 0;
			removeGroup = 0;
		}
	}
	printf("Insert:\t%d\n", insertCounter);
	printf("Search:\t%d\n", searchCounter);
	printf("Remove:\t%d\n", removeCounter);
}
