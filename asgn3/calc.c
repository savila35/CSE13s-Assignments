#include "mathlib.h"
#include "messages.h"
#include "operators.h"
#include "stack.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
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

    int loop = 0;
    while (1) { //input loop
        double x = 0;
        char input_line[STACK_CAPACITY];
        char *saveptr;
        //bool error = false;
        fgets(input_line, STACK_CAPACITY, stdin);
        const char *token = strtok_r(input_line, " ", &saveptr);
        while (token != NULL) {
            printf("here");
            if (parse_double(token, &x)) {
                printf("%f", x);
            }

            token = strtok_r(NULL, " ", &saveptr);
        }
        x++;
        if (loop == 1) {
            return 0;
        }
        loop++;
    }

    return 0;
}
