#include <assert.h>
#include <stdio.h>

#include "stack.h"
#include "operators.h"
#include "mathlib.h"


int main(void) {
	
	// testing stack	
	double a = 0.0;

    	stack_clear();
	assert(stack_peek(&a) == false);
	assert(stack_pop(&a) == false);

    	/*fill in stack*/
	for (int i = 1; i <= STACK_CAPACITY; ++i) {
        assert(stack_push(1.0 * i) == true);
	}

	assert(stack_push(65.0) == false);
	
	
	 // testing operators

	 assert(apply_binary_operator(operator_add));
	 assert(apply_binary_operator(operator_sub));
	 assert(apply_binary_operator(operator_mul));
	 assert(apply_binary_operator(operator_div));

	 // testing mathlib

	 assert(Abs(-10) == 10);
	 assert(Abs(3.4) == 3.4);

	 assert(Abs(Sin(2) - sin(2)) < EPSILON);
	printf("%f",Sin(M_PI));

	 assert(Abs(Cos(2) - cos(2)) < EPSILON);
}
