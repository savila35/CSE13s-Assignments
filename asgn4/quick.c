#include "quick.h"

#include "sorting.h"

#include <stdio.h>

void quick_sort(Stats *stats, int *A, int n) {
    quick_sorter(stats, A, 0, n - 1);
}
