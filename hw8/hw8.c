/*
 * hw8.c
 *
 *  Created on: Dec 31, 2013
 *      Author: Administrator
 */
#include <stdio.h>
#include <stdlib.h>
#include "iputil.h"
#include "list.h"
#include "clock.h"

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

void userSearch(struct prefix *list) {
	printf("Search for prefix(ex:1.2.3.4/32) :");
	char line[1024];
	scanf("%[^\n]", line);
	struct prefix* ip = parseIpFromChar(line);
	search(ip->ip, ip->len, list);
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

void run() {
	char* routingName = "routing_table";
	char* insertName = "inserted_prefixes";
	char* removeName = "deleted_prefixes";
	char* searchName = "trace_file.txt";

	int lineCount = 0;
	struct prefix *routingList = input(routingName, &lineCount);
	struct prefix *insertList = input(insertName, &lineCount);
	struct prefix *removeList = input(removeName, &lineCount);
	struct prefix *searchList = input(searchName, &lineCount);

	//printStructPrefixList(routingList);

	struct prefix *curr = insertList;
	while (curr != NULL) {
		routingList = addSorted(curr->ip, curr->len, routingList);
		curr = curr->next;
	}

	//printStructPrefixList(routingList);

	curr = removeList;
	while (curr != NULL) {
		routingList = delete(curr->ip, curr->len, routingList);
		curr = curr->next;
	}

	curr = searchList;
		while (curr != NULL) {
			search(curr->ip, curr->len, routingList);
			curr = curr->next;
		}

	//printStructPrefixList(routingList);

	printSummary();
	//userSearch(routingList);
}

void clockTest() {
	unsigned long long int begin,end;
	begin = rdtsc_64bits();
	/*---------------------------
	 your function
	 ---------------------------*/
	end = rdtsc_64bits();

	printf("Execute cycles %llu \n", (end - begin));
}
int main(int argc, const char* argv[]) {
	setvbuf(stdout, NULL, _IONBF, 0);
//testParse();
	//testRead();
//testList();
	run();
	clockTest();
	printf("Finished\n");
	return 0;
}
