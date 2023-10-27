#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "mathlib.h"

double Abs(double x) {
	if (x >= 0) {
		return x;
	} else {
		double res =  -1 * x;
		return res;
	}
}

double Sqrt(double x) {
	// Check domain.
	if (x < 0) {
      		return nan("nan");
   	}
   	double old = 0.0;
   	double new = 1.0;
   	while (Abs(old - new) > EPSILON) {
      		// Specifically, this is the Babylonian method--a simplification of
      		// Newton's method possible only for Sqrt(x).
      		old = new;
      		new = 0.5 * (old + (x / old));
	}
	return new; 
}

double Sin(double x) {
	x = fmod(x, 2 * M_PI);
	if (x < 0) {
		x += (2 * M_PI);
	}

	double res = 0.0;
	int sign = 1;
	double term = x;
	double pwr_mult = x * x;
	double factorial = 1.0;
	double prev_fact = 2.0;
	double pwr = x;
	int n = 1;
	
	while(Abs(term) >= EPSILON) {
		res += sign * term;
		sign = -sign;
		factorial *= prev_fact * (2 * n + 1);
		pwr *= pwr_mult;
		term = pwr / factorial;
		n++;
		prev_fact = 2 * n;
	}
	return res;
}

double Cos(double x) {
	x = fmod(x, 2 * M_PI);
	if (x < 0) {
		x += (2 * M_PI);
	}

	double res = 0.0;
	int sign = 1;
	double term = 1;
	double pwr = x * x;
	double pwr_mult = x * x;
	double factorial = 1.0;
	double prev_fact = 1.0;
	int n = 1;

	while (Abs(term) >= EPSILON) {
		res += sign * term;
		sign = -sign;
		factorial *= prev_fact *  2 * n;
		term = pwr / factorial;
		prev_fact = 2 * n + 1;
		n++;
		pwr *= pwr_mult;
	}
	return res;	
}

double Tan(double x) {
	double sin = Sin(x);
	double cos = Cos(x);
	return sin / cos;
}
