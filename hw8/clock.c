#include<stdlib.h>
#include<stdio.h>
#include "clock.h"

unsigned long long int begin,end;

inline unsigned long long int rdtsc()//32-bit
{
	unsigned long long int x;
	asm   volatile ("rdtsc" : "=A" (x));
	return x;
}

inline unsigned long long int rdtsc_64bits()//64-bit
{
   //unsigned long long int x;
   unsigned a, d;

   __asm__ volatile("rdtsc" : "=a" (a), "=d" (d));

   return ((unsigned long long)a) | (((unsigned long long)d) << 32);
}

void clockTest(){

	begin = rdtsc_64bits();
	/*---------------------------
	your function
	---------------------------*/
	end = rdtsc_64bits();
	
	printf("Execute cycles %llu \n",(end-begin));
}
