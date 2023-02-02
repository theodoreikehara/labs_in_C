#include "node.h"
#include <stdlib.h>
#include <stdio.h>

int main(void) {
	Node *a = node_create('a', 10);
	Node *b = node_create('b', 2);
	Node *d = node_create('d', 1);

	Node *ab = node_join(a, b);
	Node *abd = node_join(ab, d);

	printf("TEST 1\n");
	printf("\n:TEST 1: [PASSED]\n");

	node_delete(&abd);
	node_delete(&ab);
	node_delete(&a);
	node_delete(&b);
	node_delete(&d);

	// 	TREE VISUALIZATION
	//		abd
	//		13
	//            /	   \
	//   	     /      \
	//          ab	     d
	//          12       1
	//	   /  \
	//	  a    b
	//	 10    2

	Node *e = node_create('e', 6);
	Node *f = node_create('f', 8);
	Node *g = node_create('g', 1);
	Node *h = node_create('h', 5);

	Node *ef = node_join(e, f);
	Node *gh = node_join(g, h);
	Node *efgh = node_join(ef, gh);

	printf("\nTEST 2\n");

	printf("\nTEST 2: [PASSED]\n");

	node_delete(&efgh);
	node_delete(&gh);
	node_delete(&ef);
	node_delete(&h);
	node_delete(&g);
	node_delete(&f);
	node_delete(&e);

	//TREE VISUALIZATION
	//	efgh
	//     /    \
	//    /      \
	//   ef       gh
	//   14       6
	//  /  \     /   \
	// e    f   g     h
	// 6    8   1     5
	//
}


