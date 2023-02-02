#include "pq.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
//	NOTE THAT THE PRIORITY QUEUE TEST FILE HAS TO BE COMPILED WITH NODE.C AND NODE.H IN ORDER TO GIVE THE CORRECT OUTPUT
int main(void) {


	printf("\n");
	puts("***********************************************");
	PriorityQueue *q = pq_create(3);
	printf("\n");

	puts("PQ_CREATE TEST: 	[PASSED]");

	if(pq_empty(q) == 1) {
		puts("PQ_EMPTY TEST(PART 1): 	[PASSED]");
	}
	else if(pq_empty(q) != 1) {
		puts("PQ_EMPTY TEST(PART 1): 	[FAILED]");
	}

	if(pq_full(q) == 0) {
		puts("PQ_FULL TEST(PART 1): 	[PASSED]");
	}
	else if(pq_empty(q) != 0) {
		puts("PQ_FULL TEST(PART 1): 	[FAILED]");
	}

	if(pq_size(q) == 0) {
		puts("PQ_SIZE TEST(PART 1): 	[PASSED]");
	}
	else if(pq_size(q) != 0) {
		puts("PQ_SIZE TEST(PART 1): 	[FAILED]");
	}

	Node *a = node_create('a', 10);
	bool test = enqueue(q, a);

	if(test == 1) {
		puts("ENQUEUE TEST(PART 1): 	[PASSED]");
	}
	else if(test != 1) {
		puts("ENQUEUE TEST(PART 1): 	[FAILED]");
	}

	Node *b = node_create('b', 3);
	test = enqueue(q, b);

	if(test == 1) {
		puts("ENQUEUE TEST(PART 2): 	[PASSED]");
	}
	else if(test != 1) {
		puts("ENQUEUE TEST(PART 2): 	[FAILED]");
	}

	Node *c = node_create('c', 7);
	test = enqueue(q, c);

	if(test == 1) {
		puts("ENQUEUE TEST(PART 3): 	[PASSED]");
	}
	else if(test != 1) {
		puts("ENQUEUE TEST(PART 3): 	[FAILED]");
	}

	Node *d = node_create('d', 7);
	test = enqueue(q, d);

	if(test != 1) {
		puts("ENQUEUE TEST(PART 4): 	[PASSED]");
	}
	else if(test == 1) {
		puts("ENQUEUE TEST(PART 4): 	[FAILED]");
	}

    printf("error at print!!!\n");
	pq_print(q);
    printf("print past!\n");
	printf("\n");



	Node *tester = node_create('o', 2);

    printf("finished creating node!\n");
	test = dequeue(q, &tester);
    printf("finished dequeue test 1\n");

	if(test == 1) {
		puts("DEQUEUE TEST(PART 1): 	[PASSED]");
	}
	else if(test != 1) {
		puts("DEQUEUE TEST(PART 1): 	[FAILED]");
	}

	pq_print(q);
	printf("\n");

	puts("PQ_PRINT TEST(PART 2): [PASSED]");

	test = dequeue(q, &tester);

	if(test == 1) {
		puts("DEQUEUE TEST(PART 2): 	[PASSED]");
	}
	else if(test != 1) {
		puts("DEQUEUE TEST(PART 2): 	[FAILED]");
	}

	pq_print(q);
	printf("\n");

	puts("PQ_PRINT TEST(PART 3): [PASSED]");

	test = dequeue(q, &tester);

	if(test == 1) {
		puts("DEQUEUE TEST(PART 3): 	[PASSED]");
	}
	else if(test != 1) {
		puts("DEQUEUE TEST(PART 3): 	[FAILED]");
		//printf("size %ld\n", q->size);
	}

	pq_print(q);
	printf("\n");

	puts("PQ_PRINT TEST(PART 4): [PASSED]");

	test = dequeue(q, &tester);

	if(test != 1) {
		puts("DEQUEUE TEST(PART 4): 	[PASSED]");
	}
	else if(test == 1) {
		puts("DEQUEUE TEST(PART 3): 	[FAILED]");
		//printf("size %ld\n", q->size);
	}

	pq_print(q);
	printf("\n");

	puts("PQ_PRINT TEST(PART 5): [PASSED]");

	pq_delete(&q);

	puts("PQ_DELETE TEST: 	[PASSED]");

	printf("\n");
	puts("***********************************************");
	printf("\n");

	return 0;
}



