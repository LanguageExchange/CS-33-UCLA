#include "stdio.h"

static float u2f (unsigned u) { 
	union U2F{
		unsigned input;
		float output;
	};
	union U2F x;
	x.input = u;
	return x.output;
}

float fpwr4 (int x){
	/* Result exponent and fraction */
	unsigned exp, frac;
	unsigned u;
	
	if (x < -74) {
		/*Too small. Return 0.0*/
		exp = 0;
		frac = 0;
	} else if (x < -63) {
		/* Denormalized result*/
		exp = 0;
		frac = 1 << (149 + 2*x);
	} else if (x < 64) {
		/* Normalized result */
		exp = 2*x + 127;
		frac = 0;
	} else {
		/* too big. Return +inf */
		exp = 255;
		frac = 0;
	}
	
	/* Pack exp and frac into 32 bits */
	u = exp << 23 | frac;
	/* Return as float*/
	return u2f(u);
}

int main (void)
{
    printf("========== [-5, 5] ===========\n");
    printf("Computed number: %f\n", fpwr4(-5));
    printf("Computed number: %f\n", fpwr4(-4));
    printf("Computed number: %f\n", fpwr4(-3));
    printf("Computed number: %f\n", fpwr4(-2));
    printf("Computed number: %f\n", fpwr4(-1));
    printf("Computed number: %f\n", fpwr4(0));
    printf("Computed number: %f\n", fpwr4(1));
    printf("Computed number: %f\n", fpwr4(2));
    printf("Computed number: %f\n", fpwr4(3));
    printf("Computed number: %f\n", fpwr4(4));
    printf("Computed number: %f\n", fpwr4(5));
    printf("========== [-61, -70] ===========\n");
    printf("Computed number: %g\n", fpwr4(-61));
    printf("Computed number: %g\n", fpwr4(-62));
    printf("Computed number: %g\n", fpwr4(-63));
    printf("Computed number: %g\n", fpwr4(-64));
    printf("Computed number: %g\n", fpwr4(-65));
    printf("Computed number: %g\n", fpwr4(-66));
    printf("Computed number: %g\n", fpwr4(-67));
    printf("Computed number: %g\n", fpwr4(-68));
    printf("Computed number: %g\n", fpwr4(-69));
    printf("Computed number: %g\n", fpwr4(-70));
    printf("========== [62, 66] ===========\n");
    printf("Computed number: %f\n", fpwr4(62));
    printf("Computed number: %f\n", fpwr4(63));
    printf("Computed number: %f\n", fpwr4(64));
    printf("Computed number: %f\n", fpwr4(65));
    printf("Computed number: %f\n", fpwr4(66));
    printf("========== [-72, -76] ===========\n");
    printf("Computed number: %g\n", fpwr4(-72));
    printf("Computed number: %g\n", fpwr4(-73));
    printf("Computed number: %g\n", fpwr4(-74));
    printf("Computed number: %g\n", fpwr4(-75));
    printf("Computed number: %g\n", fpwr4(-76));
}