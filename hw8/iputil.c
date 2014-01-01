/*
 * iputil.c
 *
 *  Created on: Dec 31, 2013
 *      Author: Administrator
 */
#include <stdlib.h>
#include <stdio.h>
#include "iputil.h"

unsigned int power2(int b) {
	unsigned int v = 2;
	int i;
	for (i = 1; i < b; i++) {
		v = v * 2;
	}

	return v;
}

void printBits(size_t const size, void const * const ptr) {
	unsigned char *b = (unsigned char*) ptr;
	unsigned char byte;
	int i, j;

	for (i = size - 1; i >= 0; i--) {
		for (j = 7; j >= 0; j--) {
			byte = b[i] & (1 << j);
			byte >>= j;
			printf("%u", byte);
		}
	}
	puts("");
}

void print_ip_with_len(unsigned int ip, unsigned char len) {
	unsigned char bytes[4];
	bytes[0] = ip & 0xFF;
	bytes[1] = (ip >> 8) & 0xFF;
	bytes[2] = (ip >> 16) & 0xFF;
	bytes[3] = (ip >> 24) & 0xFF;
	printf("%d.%d.%d.%d/%d\n", bytes[3], bytes[2], bytes[1], bytes[0], len);
}

void printStructPrefix(struct prefix p) {
	printf("%u/%d\t-->\t", p.ip, p.len);
	print_ip_with_len(p.ip, p.len);
}

void printStructPrefixList(int pos, struct prefix *list) {
	if (pos == 0) {
		printf("=== PRINT LIST OF PREFIXES ===\n");
		if (list->ip == 0 && list->len == 0) {
			printf("=EMPTY=\n");
			return;
		}
	}
	printf("%d\t", pos);
	printStructPrefix(*list);
	if (list->next > 0) {
		printStructPrefixList(pos + 1, list->next);
	}

}

struct prefix* parseIpFromChar(char* line) {
	unsigned int bytes[4];
	unsigned int len;
	//printf("%s\n", line);
	int v = sscanf(line, "%u.%u.%u.%u/%d", &bytes[3], &bytes[2], &bytes[1],
			&bytes[0], &len);
	//printf("%d: %u.%u.%u.%u/%u\n", v, bytes[3], bytes[2], bytes[1], bytes[0],
	//		len);

	//If missing lenght - calculate it
	if (v == 4) {
		if (bytes[2] == 0 && bytes[1] == 0 && bytes[0] == 0) {
			len = 8;
		} else if (bytes[1] == 0 && bytes[0] == 0) {
			len = 16;
		} else if (bytes[0] == 0) {
			len = 24;
		} else {
			len = 32;
		}
	}

	unsigned int ip = 0;
	ip |= bytes[0];
	ip |= bytes[1] << 8;
	ip |= bytes[2] << 16;
	ip |= bytes[3] << 24;
	struct prefix *ret = (struct prefix*) malloc(sizeof(struct prefix));
	ret->ip = ip;
	ret->len = len;
	ret->next = NULL;
	return ret;
}
