#include <stdio.h>
#include <math.h>

#include "mathlib.h"

int main(void) {
	FILE *fpt;
	fpt = fopen("graphs.csv", "w+");
	fprintf(fpt,"X, Sin - sin, Cos - cos, Tan - tan\n");

	for (double i=0; i <= (2*M_PI); i += 0.1) {
		double sin_diff = sin(i) - Sin(i);
		double cos_diff = cos(i) - Cos(i);
		double tan_diff = tan(i) - Tan(i);
		fprintf(fpt,"%f, %.16f, %.16f, %.16f\n", i, sin_diff, cos_diff, tan_diff);
	}

	fclose(fpt);
	return 0;
}
