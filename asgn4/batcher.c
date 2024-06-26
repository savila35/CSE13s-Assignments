#include "batcher.h"

#include <stdio.h>

void comparator(Stats *stats, int *A, int x, int y) {
    if (cmp(stats, A[y], A[x]) < 0) {
        swap(stats, &A[x], &A[y]);
    }
}

int bit_length(int n) {
    int l = 0;
    while (n > 0) {
        n = n >> 1;
        l++;
    }
    if (l == 0) {
        return 1;
    }
    return l;
}

void batcher_sort(Stats *stats, int *A, int n) {
    if (n == 0) {
        return;
    }

    int t = bit_length(n);
    int p = 1 << (t - 1);

    while (p > 0) {
        int q = 1 << (t - 1);
        int r = 0;
        int d = p;

        while (d > 0) {
            for (int i = 0; i < (n - d); i++) {
                if ((i & p) == r) {
                    comparator(stats, A, i, i + d);
                }
            }
            d = q - p;
            q = q >> 1;
            r = p;
        }
        p = p >> 1;
    }
}
