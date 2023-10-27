#include <stdio.h>
#include <math.h>
#include <unistd.h>

#include "messages.h"
#include "stack.h"
#include "mathlib.h"
#include "operators.h"

#define OPTIONS "hm"

int main(int argc, char **argv) {
	const unary_operator_fn *unary_operators = my_unary_operators;

	int opt;
	while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
		switch (opt) {
			case 'h':
				printf(USAGE,argv[0]);
				return 0;
				break;
			case 'm':
				unary_operators = libm_unary_operators;
				break;
			default:
				printf(USAGE, argv[0]);
				return 1;
		}
	}

	

	return 0;
}
