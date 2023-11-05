#include "stats.h"

#include <stdbool.h>

int max_child(Stats *stats, int *A, int first, int last);

void fix_heap(Stats *stats, int *A, int first, int last);

void build_heap(Stats *stats, int *A, int first, int last);

int partition(Stats *stats, int *A, int lo, int hi);

void quick_sorter(Stats *stats, int *A, int lo, int hi);

void comparator(Stats *stats, int *A, int x, int y);

int bit_length(int n);
