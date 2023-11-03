#include <stdio.h>

#include "stats.h"
#include "insert.h"

void insertion_sort(Stats *stats, int *arr, int length) {
	for (int i = 0; i < length; i++) {
		int j = i;
		int temp = arr[i];
		
		while (j >= 1 && cmp(stats, temp, arr[j-1] == -1)) {
			arr[j] = move(stats, arr[j-1]);
			j -= 1;
		}
	arr[j] = temp;
	}
}
