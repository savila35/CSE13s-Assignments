#include <stdio.h>

#include "shell.h"
#include "gaps.h"

void shell_sort(Stats *stats, int *A, int n) {
	for (int i = 0; i < GAPS; i++) {
		for (int j = gaps[i]; j < n; j++) {
		       int k = j;
		       int temp = A[j];
		       while (k >= gap[i] && cmp(stats, temp, A[k-gap[i]] == -1)) {
			       A[k] = move(stats, A[k-gap[i]]);
			       k = k - gap[i];
		       }
		A[k] = move(stats, temp);
		}
	}		
}
