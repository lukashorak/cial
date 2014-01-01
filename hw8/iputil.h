/*
 * iputil.h
 *
 *  Created on: Dec 31, 2013
 *      Author: Administrator
 */

#ifndef IPUTIL_H_
#define IPUTIL_H_

struct prefix {
	unsigned int ip;
	unsigned char len;
	struct prefix *next;
};

void print_ip_with_len(unsigned int ip, unsigned char len);
void printStructPrefix(struct prefix p);
struct prefix* parseIpFromChar(char* line);
void printStructPrefixList(int pos, struct prefix *list);

#endif /* IPUTIL_H_ */
