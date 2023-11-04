#include "heap.h"

#include "sorting.h"

#include <stdio.h>

void heap_sort(Stats *stats, int *A, int n) {
    int first = 0;
    int last = n - 1;
    build_heap(stats, A, first, last);
    for (int leaf = last; leaf > first; leaf--) {
        swap(stats, &A[leaf], &A[first]);
        fix_heap(stats, A, first, leaf - 1);
    }
}
