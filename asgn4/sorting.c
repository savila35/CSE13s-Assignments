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
