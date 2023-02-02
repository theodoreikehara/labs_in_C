#include "code.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	Code c = code_init();
	uint32_t size = code_size(&c);

	puts("*****************************************************************");
	if(size == 0) {
		puts("CODE_SIZE TEST:		[PASSED]");
	}
	else if(size == 0) {
		puts("CODE_SIZE TEST:		[FAILED]");
	}

	bool test = code_empty(&c);
	if(test == 1) {
		puts("CODE_EMPTY TEST:	[PASSED]");
	}
	else if(test != 1) {
		puts("CODE_EMPTY TEST:	[FAILED]");
	}

	test = code_push_bit(&c, 0x0A);
	if(test == 1) {
		puts("PUSH_BIT TEST:		[PASSED]");
	}
	else if(test != 1) {
		puts("PUSH_BIT TEST:		[FAILED]");
	}


	test = code_push_bit(&c, 0x0A);
	if(test == 1) {
		puts("PUSH_BIT TEST:		[PASSED]");
	}
	else if(test != 1) {
		puts("PUSH_BIT TEST:		[FAILED]");
	}

	test = code_push_bit(&c, 0xFF);
	if(test == 1) {
		puts("PUSH_BIT TEST:		[PASSED]");
	}
	else if(test != 1) {
		puts("PUSH_BIT TEST:		[FAILED]");
	}

	uint8_t bit = 0;
	test = code_push_bit(&c, 1);
	//code_print(&c);
	code_push_bit(&c, 0);
	//code_print(&c);
	code_push_bit(&c, 1);
	//code_print(&c);
	code_push_bit(&c, 0);
	//code_print(&c);
	code_push_bit(&c, 0);
	//code_print(&c);
	code_push_bit(&c, 0);
	//code_print(&c);
	code_push_bit(&c, 1);
	code_print(&c);
	code_pop_bit(&c, &bit);
	//code_push_bit(&c, 1);
	//code_print(&c);
	printf("popped bit = %d\n", bit);
	code_print(&c);
	puts("*****************************************************************");

}
