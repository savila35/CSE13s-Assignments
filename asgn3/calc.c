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
    while (1) { //input loop
        double x = 0;
        char input_line[1024];
        char *saveptr;
        bool error = false;

        fprintf(stderr, "> ");
        if (fgets(input_line, 1024, stdin) == NULL) {
            break;
        }
        for (unsigned long i = 0; i < strlen(input_line); i++) {
            if (input_line[i] == '\n') {
                input_line[i] = '\0';
            }
        }

        const char *token = strtok_r(input_line, " ", &saveptr);

        while (token != NULL && !error) {
            if (parse_double(token, &x)) {
                if (!stack_push(x)) {
                    fprintf(stderr, ERROR_NO_SPACE, x);
                    stack_clear();
                    error = true;
                }
            } else if (strlen(token) > 1) {
                fprintf(stderr, ERROR_BAD_STRING, token);
                error = true;
            } else if (binary_operators[(unsigned) *token] != 0
                       && binary_operators[(unsigned) *token] != NULL) {
                if (!apply_binary_operator(binary_operators[(unsigned) *token])) {
                    fprintf(stderr, ERROR_BINARY_OPERATOR);
                    stack_clear();
                    error = true;
                }
            } else if (unary_operators[(unsigned) *token] != 0
                       && unary_operators[(unsigned) *token] != NULL) {
                if (!apply_unary_operator(unary_operators[(unsigned) *token])) {
                    fprintf(stderr, ERROR_UNARY_OPERATOR);
                    stack_clear();
                    error = true;
                }
            } else {
                fprintf(stderr, ERROR_BAD_CHAR, *token);
                stack_clear();
                error = true;
            }

            token = strtok_r(NULL, " ", &saveptr);
        }

        stack_print();
        stack_clear();
        if (!error) {
            printf("\n");
        }
    }

    return 0;
}
