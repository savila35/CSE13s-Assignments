#include "stack.h"

#include <stdio.h>

double stack[STACK_CAPACITY] = { 0 };

int stack_size = 0;

bool stack_push(double item) {
    if (stack_size == STACK_CAPACITY) {
        return 0;
    } else {
        stack[stack_size] = item;
        ++stack_size;
        return 1;
    }
}

bool stack_peek(double *item) {
    if (stack_size == 0) {
        return 0;
    } else {
        *item = stack[stack_size - 1];
        return 1;
    }
}

bool stack_pop(double *item) {
    if (stack_size == 0) {
        return 0;
    } else {
        *item = stack[stack_size - 1];
        --stack_size;
        return 1;
    }
}

void stack_clear(void) {
    stack_size = 0;
}

void stack_print(void) {
    // make sure we don't print stack[0] when it is empty
    if (stack_size == 0) {
        return;
    }
    //print the first element with 10 decimal places
    printf("%.10f", stack[0]);
    //print the remaining elements (if any), with a space before each one
    for (int i = 1; i < stack_size; i++) {
        printf(" %.10f", stack[i]);
    }
}
