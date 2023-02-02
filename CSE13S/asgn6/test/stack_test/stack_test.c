#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//note: has to be compiled with node.c

int main(void) {
	printf("\n");
	puts("****************************************************");
	Stack *s = stack_create(3);
	puts("STACK_CREATE TEST:		[PASSED]");

	bool test = stack_empty(s);
	if(test == 1) {
		puts("STACK_EMPTY TEST(PART 1):	[PASSED]");
	}
	else if(test != 1) {
		puts("STACK_EMPTY TEST(PART 1):	[FAILED]");
	}

	test = stack_full(s);
	if(test != 1) {
		puts("STACK_FULL TEST(PART 1):	[PASSED]");
	}
	else if(test == 1)  {
		puts("STACK_FULL TEST(PART 1): [FAILED]");
	}

	uint32_t size_test = stack_size(s);
	if(size_test == 0) {
		puts("STACK_SIZE TEST(PART 1):	[PASSED]");
	}
	else if(size_test != 0) {
		puts("STACK_SIZE TEST(PART 1):	[FAILED]");
	}

	Node *a = node_create('a', 2);
	test = stack_push(s, a);
	if (test == 1) {
		puts("STACK_PUSH TEST(PART 1):	[PASSED]");
	}
	else if(test != 1) {
		puts("STACK PUSH TEST(PART 1):	[FAILED]");
	}

	Node *b = node_create('b', 3);
	test = stack_push(s, b);
	if (test == 1) {
		puts("STACK_PUSH TEST(PART 2):	[PASSED]");
	}
	else if(test != 1) {
		puts("STACK PUSH TEST(PART 2):	[FAILED]");
	}

	Node *c = node_create('c', 5);
	test = stack_push(s, c);
	if (test == 1) {
		puts("STACK_PUSH TEST(PART 3):	[PASSED]");
	}
	else if(test != 1) {
		puts("STACK PUSH TEST(PART 3):	[FAILED]");
	}

	test = stack_full(s);
	if(test == 1) {
		puts("STACK_FULL TEST(PART 2):	[PASSED]");
	}
	else if(test != 1)  {
		puts("STACK_FULL TEST(PART 2): [FAILED]");
	}

	stack_print(s);
	puts("STACK_PRINT TEST(PART 1):	[PASSED]");

	Node *d = node_create('d', 7);
	test = stack_push(s, d);
	if (test != 1) {
		puts("STACK_PUSH TEST(PART 4):	[PASSED]");
	}
	else if(test == 1) {
		puts("STACK PUSH TEST(PART 4):	[FAILED]");
	}

	Node *tester = node_create('e', 3);
	test = stack_pop(s, &tester);
	if(test == 1) {
		puts("STACK_POP TEST(PART 1):		[PASSED]");
	}
	else if(test != 1) {
		puts("STACK_POP TEST(PART 1):		[FAILED]");
	}

	stack_print(s);
	puts("STACK_PRINT TEST(PART 2):	[PASSED]");

	printf("current stack size: %u\n", stack_size(s));
	while(stack_empty(s)!=true) {
		test = stack_pop(s, &tester);
	}

	test = stack_pop(s, &tester);
	//test = stack_pop(s, &tester);
	stack_print(s);

	if(test != 1) {
		puts("STACK_POP TEST(PART 2):		[PASSED]");
	}
	else if(test == 1) {
		puts("STACK_POP TEST(PART 2):		[FAILED]");
	}


	stack_print(s);

	puts("STACK_PRINT TEST(PART 3):	[PASSED]");

	stack_delete(&s);

	puts("STACK_DELETE TEST:		[PASSED]");
	puts("****************************************************");
	printf("\n");

	return 0;
}

