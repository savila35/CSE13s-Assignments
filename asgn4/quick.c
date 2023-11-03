#include <stdio.h>

#include "quick.h"

void quick_sort(Stats *stats, int *A, int n) {
	quick_sorter(A, 0, n - 1);
}
