/*
 * iputil.c
 *
 *  Created on: Dec 31, 2013
 *      Author: Administrator
 */
#include "iputil.h"

void print_ip_with_len(unsigned int ip, unsigned char len) {
	unsigned char bytes[4];
	bytes[0] = ip & 0xFF;
	bytes[1] = (ip >> 8) & 0xFF;
	bytes[2] = (ip >> 16) & 0xFF;
	bytes[3] = (ip >> 24) & 0xFF;
	printf("%d.%d.%d.%d/%d\n", bytes[3], bytes[2], bytes[1], bytes[0], len);
}

void printStructPrefix(struct prefix p) {
	printf("%d/%d\n", p.ip, p.len);
	print_ip_with_len(p.ip, p.len);
}

struct prefix parseIpFromChar(char* line) {
	unsigned int bytes[4];
	unsigned int len;
	printf("%s\n", line);
	int v = sscanf(line, "%u.%u.%u.%u/%d", &bytes[3], &bytes[2], &bytes[1],
			&bytes[0], &len);
	printf("%d: %u.%u.%u.%u/%u\n", v, bytes[3], bytes[2], bytes[1], bytes[0],
			len);

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
	struct prefix ret;
	ret.ip = ip;
	ret.len = len;
	return ret;
}
