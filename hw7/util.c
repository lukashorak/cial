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
