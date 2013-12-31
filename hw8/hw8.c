/*
 * hw8.c
 *
 *  Created on: Dec 31, 2013
 *      Author: Administrator
 */
#include <stdio.h>
#include "iputil.h"

void testParse() {

	struct prefix p1;
	p1.ip = 12345;
	p1.len = 8;
	printStructPrefix(p1);

	char* line2 = "1.2.3.4/16";
	struct prefix p2 = parseIpFromChar(line2);
	printStructPrefix(p2);

	char* line3 = "20.30.40.0";
	struct prefix p3 = parseIpFromChar(line3);
	printStructPrefix(p3);

	char* line4 = "255.255.255.255";
	struct prefix p4 = parseIpFromChar(line4);
	printStructPrefix(p4);
}

int main(int argc, const char* argv[]) {
	testParse();
	printf("Finished");
	return 0;
}
