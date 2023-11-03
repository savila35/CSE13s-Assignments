#include <stdio.h>

#include "heap.h"

void heap_sort(Stats *stats, int *A, int n) {
	int first = 0;
	int last = n - 1;
	build_heap(A, first, last);

}
