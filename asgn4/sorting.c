#include "sorting.h"

#include "batcher.h"
#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "Hahbsqin:p:r:"

#define USAGE                                                                                      \
    "SYNOPSIS\n"                                                                                   \
    "   A collection of comparison-base sorting algorithms.\n\n"                                   \
    "USAGE\n"                                                                                      \
    "   %s [-Hahbsqi] [-n length] [-p elements] [-r seed]\n\n"                                     \
    "OPTIONS\n"                                                                                    \
    "   -H              Display program help and usage.\n"                                         \
    "   -a              Enable all sorts.\n"                                                       \
    "   -h              Enable Heap Sort.\n"                                                       \
    "   -b              Enable Batcher Sort.\n"                                                    \
    "   -s              Enable Shell Sort.\n"                                                      \
    "   -q              Enable Quick Sort.\n"                                                      \
    "   -i              Enable Insertion Sort.\n"                                                  \
    "   -n length       Specify number of array elements (default: 100).\n"                        \
    "   -p elements     Specify number of elements to print (default: 100).\n"                     \
    "   -r seed         Specify random seed (default: 13371453).\n"

// heap sort helpers
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

// quick sort helpers
int partition(Stats *stats, int *A, int lo, int hi) {
    int i = lo - 1;
    for (int j = lo; j < hi; j++) {
        if (cmp(stats, A[j], A[hi]) < 0) {
            i++;
            swap(stats, &A[j], &A[i]);
        }
    }
    i++;
    swap(stats, &A[i], &A[hi]);
    return i;
}

void quick_sorter(Stats *stats, int *A, int lo, int hi) {
    if (lo < hi) {
        int p = partition(stats, A, lo, hi);
        quick_sorter(stats, A, lo, p - 1);
        quick_sorter(stats, A, p + 1, hi);
    }
}

// batcher helpers
void comparator(Stats *stats, int *A, int x, int y) {
    if (cmp(stats, A[y], A[x]) == -1) {
        swap(stats, &A[x], &A[y]);
    }
}

int bit_length(int n) {
    int l = 0;
    while (n > 0) {
        n = n >> 1;
        l++;
    }
    return l;
}

// sorting helpers
void print_elements(int *A, int size, int elements) {
    int j = elements;
    if (size < elements) {
        j = size;
    }
    for (int i = 0; i < j; i++) {
        printf("%13d", A[i]);
        if ((i + 1) % 5 == 0) {
            printf("\n");
        }
        if ((i + 1) % 5 != 0 && i + 1 >= j) {
            printf("\n");
        }
    }
}

void make_array(int *A, int seed, int size, int mask) {
    srandom(seed);
    for (int i = 0; i < size; i++) {
        A[i] = random() & mask;
    }
}

int main(int argc, char **argv) {
    Set set = set_empty();
    int heap = 0;
    int batcher = 1;
    int shell = 2;
    int quick = 3;
    int insert = 4;
    int elements = 100;
    int seed = 13371453;
    int size = 100;

    int opt;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'H':
            printf(USAGE, argv[0]);
            return 0;
            break;
        case 'a': set = set_universal(); break;
        case 'h': set = set_insert(set, heap); break;
        case 'b': set = set_insert(set, batcher); break;
        case 's': set = set_insert(set, shell); break;
        case 'q': set = set_insert(set, quick); break;
        case 'i': set = set_insert(set, insert); break;
        case 'n': size = (int) strtoull(optarg, NULL, 10); break;
        case 'p': elements = (int) strtoull(optarg, NULL, 10); break;
        case 'r': seed = (int) strtoull(optarg, NULL, 10); break;
        default: fprintf(stderr, USAGE, argv[0]); return 1;
        }
    }

    if (set == 0x00) {
        fprintf(stderr, "Select at least one sort to perform.\n");
        fprintf(stderr, USAGE, argv[0]);
        return 1;
    }

    Stats stats;
    int mask = 0x03fffffff;
    srandom(seed);
    int *A = malloc(size * sizeof(mask));

    if (set_member(set, insert)) {
        reset(&stats);
        make_array(A, seed, size, mask);
        insertion_sort(&stats, A, size);
        print_stats(&stats, "Insertion Sort", size);
        print_elements(A, size, elements);
    }
    if (set_member(set, heap)) {
        reset(&stats);
        make_array(A, seed, size, mask);
        heap_sort(&stats, A, size);
        print_stats(&stats, "Heap Sort", size);
        print_elements(A, size, elements);
    }
    if (set_member(set, shell)) {
        reset(&stats);
        make_array(A, seed, size, mask);
        shell_sort(&stats, A, size);
        print_stats(&stats, "Shell Sort", size);
        print_elements(A, size, elements);
    }
    if (set_member(set, quick)) {
        reset(&stats);
        make_array(A, seed, size, mask);
        quick_sort(&stats, A, size);
        print_stats(&stats, "Quick Sort", size);
        print_elements(A, size, elements);
    }
    if (set_member(set, batcher)) {
        reset(&stats);
        make_array(A, seed, size, mask);
        batcher_sort(&stats, A, size);
        print_stats(&stats, "Batcher Sort", size);
        print_elements(A, size, elements);
    }

    free(A);

    return 0;
}
