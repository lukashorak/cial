/*
 * util.s
 *
 *  Created on: 25 Dec 2013
 *      Author: Lukas
 */
 #include <stdio.h>

int min(int a, int b) {
	if (a > b) {
		return b;
	} else {
		return a;
	}
}

int max(int a, int b) {
	if (a >= b) {
		return a;
	} else {
		return b;
	}
}

int compare_int(const void * elem1, const void * elem2) {
	int f = *((int*) elem1);
	int s = *((int*) elem2);
	if (f > s)
		return 1;
	if (f < s)
		return -1;
	return 0;
}
