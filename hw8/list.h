/*
 * list.h
 *
 *  Created on: 2 Jan 2014
 *      Author: Lukas
 */

#ifndef LIST_H_
#define LIST_H_

struct prefix* input(char* fileName, int *lc);
struct prefix* addSorted(unsigned int ip, unsigned char len,
		struct prefix *list);
struct prefix* delete(unsigned int ip, unsigned char len, struct prefix *list);
struct prefix* search(unsigned int ip, unsigned char len, struct prefix *list);

void printSummary();

#endif /* LIST_H_ */
