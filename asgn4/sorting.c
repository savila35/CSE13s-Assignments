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
#include <unistd.h>

#define OPTIONS "Hahbsqin:p:r:"

#define USAGE                                                                                      \
    "SYNOPSIS\n"                                                                                   \
    "   A collection of comparison-base sorting algorithms.\n\n"                                   \
    "USAGE\n"                                                                                      \
    "   ./%s [-Hahbsqi] [-n length] [-p elements] [-r seed]\n\n"                                   \
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
    if (right <= last && cmp(stats, A[left], A[right]) == -1) {
        return right;
    }
    return left;
}

void fix_heap(Stats *stats, int *A, int first, int last) {
    bool done = false;
    int parent = first;
    while ((2 * parent + 1) <= last && !done) {
        int largest_child = max_child(stats, A, parent, last);
        if (cmp(stats, A[parent], A[largest_child]) == -1) {
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
        if (cmp(stats, A[j], A[hi]) == -1) {
            i++;
            swap(stats, &A[j], &A[hi]);
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

int main(int argc, char **argv) {
    Set set = 0x00;
    int heap = 0x01;
    int batcher = 0x02;
    int shell = 0x04;
    int quick = 0x08;
    int insert = 0x10;
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
        case 'n': break;
        case 'p': break;
        case 'r': break;
        default: fprintf(stderr, USAGE, argv[0]); return 1;
        }
    }
    (void) seed;
    (void) elements;
    (void) size;
    return 0;
}
