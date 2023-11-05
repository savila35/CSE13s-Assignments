#include "heap.h"

#include <stdbool.h>
#include <stdio.h>

int max_child(Stats *stats, int *A, int first, int last) {
    int left = 2 * first + 1;
    int right = 2 * first + 2;
    if (right <= last && cmp(stats, A[left], A[right]) < 0) {
        return right;
    }
    return left;
}

void fix_heap(Stats *stats, int *A, int first, int last) {
    bool done = false;
    int parent = first;
    while ((2 * parent + 1) <= last && !done) {
        int largest_child = max_child(stats, A, parent, last);
        if (cmp(stats, A[parent], A[largest_child]) < 0) {
            swap(stats, &A[parent], &A[largest_child]);
            parent = largest_child;
        } else {
            done = true;
        }
    }
}

void build_heap(Stats *stats, int *A, int first, int last) {
    if (last > 0) {
        for (int parent = (last - 1) / 2; parent > first - 1; parent--) {
            fix_heap(stats, A, parent, last);
        }
    }
}

void heap_sort(Stats *stats, int *A, int n) {
    int first = 0;
    int last = n - 1;
    build_heap(stats, A, first, last);
    for (int leaf = last; leaf > first; leaf--) {
        swap(stats, &A[leaf], &A[first]);
        fix_heap(stats, A, first, leaf - 1);
    }
}
