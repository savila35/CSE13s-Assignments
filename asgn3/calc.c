#include "mathlib.h"
#include "messages.h"
#include "operators.h"
#include "stack.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>

#define OPTIONS "hm"

int main(int argc, char **argv) {
    const unary_operator_fn *unary_operators = my_unary_operators;

    int opt;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            printf(USAGE, argv[0]);
            return 0;
            break;
        case 'm': unary_operators = libm_unary_operators; break;
        default: printf(USAGE, argv[0]); return 1;
        }
    }
    assert(apply_unary_operator(unary_operators['s']) == false);

    return 0;
}
