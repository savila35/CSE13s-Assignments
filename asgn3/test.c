#include "stack.h"

#include <assert.h>
#include <stdio.h>

int main(void) {
    double a = 0.0;

    stack_clear();
    assert(stack_peek(&a) == false);
    assert(stack_pop(&a) == false);

    /*fill in stack*/
    for (int i = 1; i <= STACK_CAPACITY; ++i) {
        assert(stack_push(1.0 * i) == true);
    }

    assert(stack_push(65.0) == false);

    //stack_print();
}
